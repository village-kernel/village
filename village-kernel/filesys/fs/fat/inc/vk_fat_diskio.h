//###########################################################################
// vk_fat_diskio.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_FAT_DISk_IO_H__
#define __VK_FAT_DISk_IO_H__

#include "vk_dev_stream.h"


/// @brief FatDiskio
class FatDiskio
{
public:
    //Enumerates
    enum FATType
    {
        _NoneType = 0,
        _FAT12,
        _FAT16,
        _FAT32,
        _EXTFAT,
    };

    //Structures
    struct BS
    {
        uint8_t jmpBoot[3];
        uint8_t OEMName[8];
    } __attribute__((packed));

    struct BPB
    {
        uint16_t bytesPerSec;
        uint8_t  secPerClust;
        uint16_t rsvdSecCnt;
        uint8_t  numFATs;
        uint16_t rootEntCnt;
        uint16_t totSec16;
        uint8_t  media;
        uint16_t FATSz16;
        uint16_t secPerTrk;
        uint16_t numHeads;
        uint32_t hiddSec;
        uint32_t totSec32;
    }  __attribute__((packed));

    struct FAT1216
    {
        uint8_t  drvNum;
        uint8_t  reserved1;
        uint8_t  bootSig;
        uint32_t volID;
        uint8_t  volLab[11];
        uint8_t  filSysType[8];
        uint8_t  reserved[28];
    } __attribute__((packed));

    struct FAT32
    {
        uint32_t FATSz32;
        uint16_t extFlags;
        uint16_t FSVer;
        uint32_t rootClust;
        uint16_t FSInfo;
        uint16_t bkBootSec;
        uint8_t  reserved[12];
        uint8_t  drvNum;
        uint8_t  reserved1;
        uint8_t  bootSig;
        uint32_t volID;
        uint8_t  volLab[11];
        uint8_t  filSysType[8];
    } __attribute__((packed));

    struct DBR
    {
        BS  bs;
        BPB bpb;
        union {
            FAT1216 fat1216;
            FAT32   fat32;
        };
        uint8_t  reserved[420];
        uint16_t magic;
    } __attribute__((packed));

    struct FAT32FSInfo
    {
        uint32_t leadSig;
        uint8_t  reserved1[480];
        uint32_t structSig;
        uint32_t freeCount;
        uint32_t nextFree;
        uint8_t  reserved2[12];
        uint32_t trailSig;
    } __attribute__((packed));

    struct Info
    {
        FATType  fatType;
        uint32_t fatSize;

        uint32_t rsvdSecCnt;
        uint32_t totalSectors;
        uint32_t countOfClusters;

        uint32_t startOfFatSector;
        uint32_t endedOfFatSector;

        uint32_t rootClust;
        uint32_t firstRootSector;
        uint32_t countOfRootSecs;

        uint32_t firstDataSector;
        uint32_t countOfDataSecs;

        uint32_t entriesPerSec;
        uint32_t bytesPerSec;
        uint32_t secPerClust;
    };
private:
    //Static constants
    static const uint16_t magic = 0xaa55;
    static const uint8_t  dir_entry_size = 32;
    static const uint16_t fat12_eoc_flag = 0xff8;
    static const uint16_t fat16_eoc_flag = 0xfff8;
    static const uint32_t fat32_eoc_flag = 0xffffff8;

    //Driver Members
    DevStream* device;
    uint32_t   startingLBA;
    Info       info;

    //Methods
    bool CheckFileSystem();
public:
    //Method
    bool Setup(DevStream* device, uint32_t startingLBA);
    void Exit();

    uint32_t WriteSector(char* data, uint32_t sector, uint32_t secSize = 1);
    uint32_t ReadSector(char* data, uint32_t sector, uint32_t secSize = 1);

    uint32_t ClusterToSector(uint32_t clust);
    
    uint32_t GetNextCluster(uint32_t clust);
    uint32_t SetNextCluster(uint32_t clust);
    uint32_t ClearPrevCluster(uint32_t clust);

    uint32_t ReadCluster(char* data, uint32_t clust, uint32_t clustSize);
    uint32_t WriteCluster(char* data, uint32_t clust, uint32_t clustSize);
    uint32_t ClearCluster(uint32_t clust, uint32_t clustSize);

    uint32_t AllocCluster(uint32_t clustSize = 1);
    uint32_t FreeCluster(uint32_t clust, uint32_t clustSize = 1);
    
    Info& GetInfo();
};

#endif //!__VK_FAT_DISk_IO_H__
