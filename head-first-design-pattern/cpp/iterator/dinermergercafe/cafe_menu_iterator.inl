/* $Id$ */

inline Cafe_Menu_Iterator::Cafe_Menu_Iterator(ITEM_MAP &items) : items_(items)
{ 
	it_ = items_.begin();
}

inline Cafe_Menu_Iterator::~Cafe_Menu_Iterator()
{ }

inline Menu_Item* Cafe_Menu_Iterator::next()
{
	return &((it_++)->second);
}

inline bool Cafe_Menu_Iterator::has_next()
{
	return it_ != items_.end();
}

