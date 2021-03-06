extern char fName[];
extern struct PCB* PCBTable[];
int countTotalPages (FILE* f);
char* getFileName(FILE* f);
int findFrame (FILE* page);
FILE* findPage (int pageNumber, FILE* f);
int updateFrame (int frameNumber, int victimFrame, FILE* page);
int findVictim (struct PCB* p);
int updatePageTable (struct PCB* p, int pageNumber, int frameNumber, int victimFrame);
int launcher (FILE* p, char* name);
