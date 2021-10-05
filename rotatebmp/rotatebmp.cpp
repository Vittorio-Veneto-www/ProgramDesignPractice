#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <fstream>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

//位图文件头定义
typedef struct tagBITMAPFILEHEADER {
//  WORD bfType;//单独读取，结构体中就不定义了
    DWORD bfSize;//文件大小
    WORD bfReserved1;//保留字
    WORD bfReserved2;//保留字
    DWORD bfOffBits;//从文件头到实际位图数据的偏移字节数
} BITMAPFILEHEADER;

//位图信息头定义
typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;//信息头大小
    DWORD biWidth;//图像宽度
    DWORD biHeight;//图像高度
    WORD biPlanes;//位平面数
    WORD biBitCount;//每像素位数
    DWORD biCompression;//压缩类型
    DWORD biSizeImage;//压缩图像大小字节数
    DWORD biXPelsPerMeter;//水平分辨率
    DWORD biYPelsPerMeter;//垂直分辨率
    DWORD biClrUsed;//位图实际用到的色彩数
    DWORD biClrImportant;//本位图中重要的色彩数
} BITMAPINFOHEADER;

//像素信息
typedef struct tagIMAGEDATA_24
{
    BYTE blue;
    BYTE green;
    BYTE red;
} DATA_24;

typedef struct tagIMAGEDATA_32
{
    BYTE blue;
    BYTE green;
    BYTE red;
    BYTE alpha;
} DATA_32;

template <class T>
class BmpFile
{
    public:
        BmpFile(const char* filePath);
        ~BmpFile();
        void rotate90(const char* filePath);
        void readfile(const char* filePath);
        void clone(const char* filePath);
        int getPSize();
    private:
        BITMAPFILEHEADER strHead;
        BITMAPINFOHEADER strInfo;
        BYTE* appendInfo;
        int h, w;
        int mH, mW, mSize;

        WORD bfType;
        char *_src;
        void *src;
};

template <class T>
BmpFile<T>::BmpFile(const char* filePath)
{
    readfile(filePath);
}

template <class T>
BmpFile<T>::~BmpFile()
{
    delete [] _src;
    delete [] appendInfo;
}

//从指定路径读取BMP位图
template <class T>
void BmpFile<T>::readfile(const char* filePath)
{
    std::fstream binary_file(filePath, std::ios::in|std::ios::binary);
    
    if (binary_file)
    {
        //先读取文件类型
        binary_file.read((char*)&bfType, sizeof(WORD));
        if (0x4d42 != bfType)
            printf("Error:The file is not a bmp image\n");
        //读取bmp文件的文件头和信息头
        binary_file.read((char*)&strHead, sizeof(tagBITMAPFILEHEADER));
        binary_file.read((char*)&strInfo, sizeof(tagBITMAPINFOHEADER));
        appendInfo = new BYTE[strInfo.biSize - sizeof(tagBITMAPINFOHEADER)];
        binary_file.read((char*)appendInfo, strInfo.biSize - sizeof(tagBITMAPINFOHEADER));
        //获取图像的宽度，以像素为单位
        h = strInfo.biHeight;
        //获取图像的高度，以像素为单位
        w = strInfo.biWidth;
        //每一行像素的字节数必须是4的整数倍，不足用0补齐
        mH = (h * sizeof(T) / 4 + ((h * sizeof(T) % 4) ? 1 : 0)) * 4;
        mW = (w * sizeof(T) / 4 + ((w * sizeof(T) % 4) ? 1 : 0)) * 4;
        //初始化原始图片的像素数组
        _src = new char[h * mW];
        src = _src;
        //读取bmp数据信息
        binary_file.read((char*)src, h * mW);
        binary_file.close();
    }
}

template <class T>
T& getPixel(void *target, int h, int w, int mW)
{
    return *(((T*)(((char*)target) + h * mW)) + w);
}

//复制
template <class T>
void BmpFile<T>::clone(const char* filePath)
{
    std::fstream binary_file(filePath, std::ios::out|std::ios::binary);
    char *target = new char[h * mW];
    memset(target, 0, h * mW);
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            getPixel<T>(target, i, j, mW) = getPixel<T>(src, i, j, mW);
    BITMAPFILEHEADER newHead = strHead;
    BITMAPINFOHEADER newInfo = strInfo;
    newHead.bfSize = (DWORD)(h * mW + sizeof(tagBITMAPFILEHEADER) + strInfo.biSize + 2);
    newInfo.biHeight = (DWORD)h;
    newInfo.biWidth = (DWORD)w;
    newInfo.biSizeImage = (DWORD)(h * mW);
    binary_file.write((char*)&bfType, sizeof(WORD));
    binary_file.write((char*)&newHead, sizeof(tagBITMAPFILEHEADER));
    binary_file.write((char*)&newInfo, sizeof(tagBITMAPINFOHEADER));
    binary_file.write((char*)appendInfo, strInfo.biSize - sizeof(tagBITMAPINFOHEADER));
    binary_file.write((char*)target, newInfo.biSizeImage);
    binary_file.close();
    printf("clone success\n");
    delete [] target;
}

//旋转90度
template <class T>
void BmpFile<T>::rotate90(const char* filePath)
{
    std::fstream binary_file(filePath, std::ios::out|std::ios::binary);
    char *target = new char[w * mH];
    memset(target, 0, w * mH);
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            getPixel<T>(target, w - j - 1, i, mH) = getPixel<T>(src, i, j, mW);
    BITMAPFILEHEADER newHead = strHead;
    BITMAPINFOHEADER newInfo = strInfo;
    newHead.bfSize = (DWORD)(w * mH + sizeof(tagBITMAPFILEHEADER) + strInfo.biSize + 2);
    newInfo.biHeight = (DWORD)w;
    newInfo.biWidth = (DWORD)h;
    newInfo.biSizeImage = (DWORD)(w * mH);
    binary_file.write((char*)&bfType, sizeof(WORD));
    binary_file.write((char*)&newHead, sizeof(tagBITMAPFILEHEADER));
    binary_file.write((char*)&newInfo, sizeof(tagBITMAPINFOHEADER));
    binary_file.write((char*)appendInfo, strInfo.biSize - sizeof(tagBITMAPINFOHEADER));
    binary_file.write((char*)target, newInfo.biSizeImage);
    binary_file.close();
    printf("rotate success\n");
    delete [] target;
};

int getBitCount(const char* filePath)
{
    std::fstream binary_file(filePath, std::ios::in|std::ios::binary);
    BITMAPFILEHEADER strHead;
    BITMAPINFOHEADER strInfo;
    WORD bfType;

    if (binary_file)
    {
        binary_file.read((char*)&bfType, sizeof(WORD));
        binary_file.read((char*)&strHead, sizeof(tagBITMAPFILEHEADER));
        binary_file.read((char*)&strInfo, sizeof(tagBITMAPINFOHEADER));
        binary_file.close();
        return strInfo.biBitCount;
    }
    else
    {
        binary_file.close();
        printf("file does not exist\n");
        return 0;
    }
}

int main(int argc, char *argv[])
{
    //初始化BMP文件类,指定图片路径,从指定路径读取图片
    if (getBitCount(argv[1]) == 24)
    {
        BmpFile<DATA_24> *bmp = new BmpFile<DATA_24>(argv[1]);
        //bmp->clone(argv[1]);
        bmp->rotate90(argv[2]);
    }
    else
    {
        BmpFile<DATA_32> *bmp = new BmpFile<DATA_32>(argv[1]);
        //bmp->clone(argv[1]);
        bmp->rotate90(argv[2]);
    }
    return 0;
}