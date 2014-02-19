/*!
 * \file display_element.h
 * \brief The Display_Element interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef DISPLAY_ELEMENT_H
#define DISPLAY_ELEMENT_H

class Display_Element
{
public:
    Display_Element() { };
    virtual ~Display_Element() { };

	virtual void display() = 0;
};

#endif /* DISPLAY_ELEMENT_H */

