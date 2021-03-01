#pragma once
#include <string>
#include <list>
#include <algorithm>
#include <QObject>
#include <QVariant>


using std::string;

class Attribute
{
public:
	Attribute() noexcept;
	Attribute(QVariant*) noexcept;
    Attribute(QVariant*, const string&) noexcept;
	virtual ~Attribute();	
    inline bool is_root();
    inline bool is_valid();
	const string& get_name();
    inline QVariant* get_val();
    string make_dump_string();

protected:
	bool m_is_root;
	QVariant* m_val;
	string m_name;
};

class DataKeeperTree
{

public:
	DataKeeperTree() noexcept;
	DataKeeperTree(const DataKeeperTree&) noexcept;
	DataKeeperTree(DataKeeperTree*) noexcept;
	DataKeeperTree(DataKeeperTree&&) noexcept;
	DataKeeperTree(QVariant*) noexcept;
	DataKeeperTree(QVariant*, DataKeeperTree*) noexcept;
    virtual ~DataKeeperTree();

	virtual void push_child(DataKeeperTree*);
    virtual void pop_child();
    static void erase_elem(DataKeeperTree*);
    virtual void del_all_child(DataKeeperTree*); ///recursive del all m_childs

    ///GETTERS
    inline DataKeeperTree *get_parent();
    inline bool has_parent();
    inline bool has_childs();
    inline bool has_attribute();
    inline bool has_name();
    inline bool is_root();
    inline size_t childs_count(); ///return m_childs.size()


    virtual string get_dump(DataKeeperTree*);	///recursive make dump from this elem
	virtual DataKeeperTree* from_dump(string&); ///convert from string dump

private:
    void _getDump(DataKeeperTree* ,string&);

protected:
	Attribute m_atr;
	std::vector<DataKeeperTree*>* m_childs;
	DataKeeperTree* m_parent;
};

