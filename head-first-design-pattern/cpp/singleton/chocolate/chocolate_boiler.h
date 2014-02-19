/*!
 * \file chocolate_boiler.h
 * \brief The Chocolate_Boiler class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-04
 */
/* $Id$ */

#ifndef CHOCOLATE_BOILER_H
#define CHOCOLATE_BOILER_H

class Chocolate_Boiler
{
public:
	static Chocolate_Boiler* get_instance();
	static void close();
	void fill();
	void drain();
	void boil();
	bool is_empty();
	bool is_boiled();

private:
    Chocolate_Boiler();
    virtual ~Chocolate_Boiler();

private:
	bool empty_;
	bool boiled_;
	static Chocolate_Boiler *unique_;
};

#endif /* CHOCOLATE_BOILER_H */

