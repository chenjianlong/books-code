/*
 * \file debug1.c
 * \brief demo for debug1
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-23
 */
/* $Id$ */


typedef struct {
	char *data;
	int key;
} item;

item array[] = {
	{"bill", 3},
	{"neil", 4},
	{"john", 2},
	{"rick", 5},
	{"alex", 1},
};

sort(a,n)
item *a;
{
	int i = 0, j = 0;
	int s = 1;
	for(; i < n && s != 0; i++) {
		s = 0;
		for(j = 0; j < n; j++) {
			if(a[j].key > a[j+1].key) {
				item t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
				s++;
			}
		}
		n--;
	}
}

main()
{
	sort(array,5);
}
