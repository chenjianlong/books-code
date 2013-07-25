/*!
 * \file cd_data.h
 * \brief the definition of cd data
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-08
 */
/* $Id$ */

#ifndef CD_DATA_H
#define CD_DATA_H

/* The catalog table */
#define CAT_CAT_LEN			30
#define CAT_TITLE_LEN		70
#define CAT_TYPE_LEN		30
#define CAT_ARTIST_LEN		70

typedef struct {
	char catalog[CAT_CAT_LEN + 1];
	char title[CAT_TITLE_LEN + 1];
	char type[CAT_TYPE_LEN + 1];
	char artist[CAT_ARTIST_LEN + 1];
} cdc_entry;

/* The tracks table, one entry per track */
#define TRACK_CAT_LEN		CAT_CAT_LEN
#define TRACK_TTEXT_LEN		70

typedef struct {
	char catalog[TRACK_CAT_LEN + 1];
	int track_no;
	char track_txt[TRACK_TTEXT_LEN + 1];
} cdt_entry;

/* Initialization and termination functions */
int database_initialize(const int new_database);
void database_close();

/* two for simple data retrieval */
cdc_entry get_cdc_entry(const char *cd_catalog_ptr);
cdt_entry get_cdt_entry(const char *cd_catalog_ptr, const int track_no);

/* two for data addition */
int add_cdc_entry(const cdc_entry entry_to_add);
int add_cdt_entry(const cdt_entry entry_to_add);

/* two for data deletion */
int del_cdc_entry(const char *cd_catalog_ptr);
int del_cdt_entry(const char *cd_catalog_ptr, const int track_no);

/* one search function */
cdc_entry search_cdc_entry(const char *cd_catalog_ptr, int *first_call_ptr);

#endif /* !CD_DATA_H */


