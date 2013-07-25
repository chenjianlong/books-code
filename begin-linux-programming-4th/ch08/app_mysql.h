/*!
 * \file app_mysql.h
 * \brief definition of structures and function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-18
 */
/* $Id$ */

#ifndef APP_MYSQL_H
#define APP_MYSQL_H

/* A simplistic structure to represent the current CD, excluding the track information */
struct current_cd_st {
	int artist_id;
	int cd_id;
	char artist_name[100];
	char title[100];
	char catalogue[100];
};

/* A simplistic track details structure */
struct current_tracks_st {
	int cd_id;
	char track[20][100];
};

#define MAX_CD_RESULT 10
struct cd_search_st {
	int cd_id[MAX_CD_RESULT];
};

/* Database backend functions */
int database_start(char *name, char *password);
void database_end();

/* Functions for adding a CD */
int add_cd(char *artist, char *title, char *catalogue, int *cd_id);
int add_tracks(struct current_tracks_st *results);
/* Functions for finding and retrieving a CD */
int find_cds(char *search_str, struct cd_search_st *results);
int get_cd(int cdid, struct current_cd_st *dest);
int get_cd_tracks(int cd_id, struct current_tracks_st *dest);
/* Function for deleting items */
int delete_cd(int cd_id);

#endif /* !APP_MYSQL_H */

