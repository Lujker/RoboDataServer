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
    Attribute(string&) noexcept;
    Attribute(QVariant*, const string&) noexcept;
	virtual ~Attribute();	
    inline bool is_root();
    inline bool is_valid();
    inline QVariant* get_val();
	const string& get_name();
    string make_dump_string();
    bool operator!=(const Attribute&);
    bool operator==(const Attribute&);
    Attribute make_from_dump(string& str);

protected:///Members
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
    DataKeeperTree(Attribute&) noexcept;
	DataKeeperTree(QVariant*) noexcept;
	DataKeeperTree(QVariant*, DataKeeperTree*) noexcept;
    virtual ~DataKeeperTree();

    ///TREE INTERACTION
	virtual void push_child(DataKeeperTree*);
    virtual void del_all_child(DataKeeperTree*); ///recursive del all obj in m_childs
    virtual void pop_child();
    static void erase_elem(DataKeeperTree*);

    ///GETTERS
    inline DataKeeperTree *get_parent();
    inline bool has_parent();
    inline bool has_childs();
    inline bool has_attribute();
    inline bool has_name();
    inline bool is_root();
    inline size_t childs_count(); ///return m_childs.size()

    ///FIND ELEM IN STRUCT
    static DataKeeperTree *find_by_attr(DataKeeperTree*, Attribute&);
    static DataKeeperTree *find_by_name(DataKeeperTree*, string&);
    DataKeeperTree *find_root();

    ///DUMPS WORK
    virtual string get_dump(DataKeeperTree*);
    static DataKeeperTree* from_dump(string&);

private:
    void _getDump(DataKeeperTree*, string&);       ///recursive make dump from this elem
    void _parseDumpLine(DataKeeperTree*, string&); ///convert from string dump

protected: ///Members
	Attribute m_atr;
	std::vector<DataKeeperTree*>* m_childs;
	DataKeeperTree* m_parent;
};

