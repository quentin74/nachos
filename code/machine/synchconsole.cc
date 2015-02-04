#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"
static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
  readAvail = new Semaphore("read avail", 0);
  writeDone = new Semaphore("write done", 0);
  console = new console(readFile,writeFile,ReadAvail,WriteDone,0);
}
SynchConsole::~SynchConsole()
{
  delete console;
  delete writeDone;
  delete readAvail;
}
void SynchConsole::SynchPutChar(const char ch)
{

    writeDone.P();
    ASSERT(putBusy == FALSE);
    WriteFile(writeFileNo, &ch, sizeof(char));
    putBusy = TRUE;
    interrupt->Schedule(ConsoleWriteDone, (int)this, ConsoleTime,ConsoleWriteInt);
    writeDone.V();

}
char SynchConsole::SynchGetChar()
{

char ch = incoming;
   readAvail.P();
   incoming = EOF;
   return ch;
   readAvail.V();



}
void SynchConsole::SynchPutString(const char s[])
{
// ... 
}
void SynchConsole::SynchGetString(char *s, int n)
{
// ... 
}

#endif // CHANGED
