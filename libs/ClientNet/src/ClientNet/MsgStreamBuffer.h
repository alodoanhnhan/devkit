#pragma once

#include <Windows.h>

#include <cstddef>
#include <string>
#include <new>
#include <string>

#include <Test/Test.h>
#include <remodel/GlobalVar.h>
#include <BSLib/memory/MemPool.h>
#include <BSLib/_internal/custom_stl.h>


#define NEWMSG(msgid) \
if (IsOpcodeSupported(msgid, 0)) { \
    CMsgStreamBuffer pReq(msgid); \
    pReq.ToggleBefore();

#define SENDMSG() \
    pReq.ToggleAfter(); \
    SendMsg(pReq); \
}

bool IsOpcodeSupported(WORD msgid, int);


class CMsgStreamBuffer {
public: /* todo: this public is only temporary. Remove it as soon as the allocator is working properly */
    class SMsgStreamNode {
    public:
        SMsgStreamNode();

        static void *operator new(std::size_t sz);

    private:
        static GlobalVar<CMemPool<(_TAG('MSG', 1)), SMsgStreamNode, 20, 1>, 0x00EECD98> m_mempool;
        //static CMemPool<(_TAG('MSG' ,1)), SMsgStreamNode, 20, 1> m_mempool;

    private:
        int data[1024];
        char _pad[4];
        int *currentPos;
    };

public:
    explicit CMsgStreamBuffer(WORD msgid);

    virtual ~CMsgStreamBuffer();


    void ToggleBefore();

    void ToggleAfter();

    WORD msgid() const;

    void FlushRemaining();
    unsigned int m_currentReadBytes;
    //
    // Read
    //

    template<typename T>
    CMsgStreamBuffer &operator>>(T &value) {
        Read(value);
        return *this;
    }

    /// \address 0x004f7a70
    CMsgStreamBuffer &operator>>(std::n_string &str);

    template<typename T>
    void Read(T &value) {
        Read(&value, sizeof(T));
    }

    //
    // Write
    //

    CMsgStreamBuffer &operator<<(const std::n_string &str);

    CMsgStreamBuffer &operator<<(const std::string &str);

    template<typename T>
    CMsgStreamBuffer &operator<<(T value) {
        Write(&value, sizeof(value));
        return *this;
    }

public:
    void Write(const void *data, size_t size);
    void SendToClient();
    UINT32 GetLength() const;
    void Read(void* value, size_t numBytes);
public:
   // unsigned int m_currentReadBytes;
    unsigned int m_availableBytesForReading;
    unsigned char field_0xc;
    unsigned char field_0xd;
    unsigned char field_0xe;
    unsigned char field_0xf;
    SMsgStreamNode *m_node1;
    SMsgStreamNode *m_node2;
    WORD m_msgid; //0x18

    BEGIN_FIXTURE()
        ENSURE_SIZE(28) // size taken from 0x00871887
        ENSURE_OFFSET(m_msgid, 24)
    END_FIXTURE()

    RUN_FIXTURE(CMsgStreamBuffer)
};
