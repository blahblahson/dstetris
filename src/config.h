#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef struct {
    unsigned short int level;
    unsigned short int linc;
    unsigned int infinity;
    unsigned int das;
    unsigned int sspeed;
    unsigned int rseed;
} __attribute__ ((packed)) CONFIG;

void LoadConfig(CONFIG *);
void WriteConfig(const CONFIG *);

#endif /* _CONFIG_H_ */
