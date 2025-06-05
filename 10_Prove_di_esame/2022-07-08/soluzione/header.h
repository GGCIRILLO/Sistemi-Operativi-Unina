#define NUM_UPDATES 4
#define NUM_READS 5
#define NUM_READERS 3

#define MESSAGGIO 1


typedef struct {
	long type;
	int pid;
	int value;
} req; 

typedef struct {
	long sender;
	int value;
} res; 


