#ifndef LEVELS_H
#define LEVELS_H
//1 is weak, 2 is strong, 3 is fast shooting



int level1[30] =   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int level2[30] =   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int level3[30] =   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int level4[30] =   {2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
                    1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int level5[30] =   {2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
                    1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
                    3, 0, 0, 0, 3, 3, 0, 0, 0, 3};

int level6[30] =   {1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
                    2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
                    1, 0, 0, 0, 0, 0, 0, 0, 0, 1};

int level7[30] =   {2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                    3, 0, 3, 0, 3, 3, 0, 3, 0, 3,
                    0, 1, 0, 1, 0, 0, 1, 0, 1, 0};

int level8[30] =   {3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
                    1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
                    3, 1, 3, 1, 3, 1, 3, 1, 3, 1,};

int level9[30] =   {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
                    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,};

int level1Size = 10;
int level2Size = 20;
int level3Size = 20;
int level4Size = 20;
int level5Size = 24;
int level6Size = 22;
int level7Size = 24;
int level8Size = 30;
int level9Size = 30;
#endif