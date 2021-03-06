#include "../include/RaspPiCLK.h"

RaspPiCLK::RaspPiCLK()
{
    //ctor
    #define CLK_BASE               (PERI_BASE + 0x101000)
    /* CLK controller */

    #define PAGE_SIZE (4*1024)
    #define BLOCK_SIZE (4*1024)

    wxString TmpStrg;
    int   mem_fd;

    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC) ) < 0)
        {
        //wxMessageBox(wxT("can't open /dev/mem\n"),wxT("ERROR"),  wxICON_EXCLAMATION);
        exit (1);
        }

    /* mmap CLK */
    clk_map = mmap(
        NULL,               // any address in our space will do
        BLOCK_SIZE,         // map length
        PROT_READ|PROT_WRITE,   // Enable reading & writing to mapped memory
        MAP_SHARED,         // shared with other processes
        mem_fd,             // file to map
        CLK_BASE
        );

    close (mem_fd);

    if (clk_map == MAP_FAILED) {
        TmpStrg.Printf(wxT("mmap error %d\n"),(int) clk_map);
        //wxMessageBox(wxT("Error"),wxT("Error"),wxICON_EXCLAMATION,this);
        exit(-1);
        }

    clkio = (volatile unsigned int *)clk_map;
}

RaspPiCLK::~RaspPiCLK()
{
    //dtor
    wxString TmpStrg;

    /* munmap CLK */
    if (munmap(clk_map,         // address in our space will do
        BLOCK_SIZE              // map length
        ) == -1) {
        TmpStrg.Printf(wxT("munmap error %d\n"),(int) -1);
        //wxMessageBox(wxT("Error"),wxT("Error"),wxICON_EXCLAMATION,this);
        exit(-1);
        }
}


void RaspPiCLK::PWMCLK_Start(void)
{
    // source = osc and enable clock
    *(clkio + PWMCLK_CNTL) = 0x5A000000 | 0x11;
}


void RaspPiCLK::PWMCLK_Stop(void)
{
    // stop clock and waiting for busy doesn't work, so kill clock
    *(clkio + PWMCLK_CNTL) = 0x5A000000 | (1<<5);

    usleep(10);

    // wait until busy flag is clear
    while((*(clkio + PWMCLK_CNTL)) &  (1<<7))
      {}; // 0x00000080
}


void RaspPiCLK::PWMCLK_SetDivisor(unsigned int Divisor)
{
    // Set divisor
    // 0101 1010 = 0x5A
    *(clkio + PWMCLK_DIV) = 0x5A000000 | (Divisor << 12);
}



