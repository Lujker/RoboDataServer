#pragma once
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>
#include <QObject>
#include <QVariant>

using std::string;

std::vector<string> split (const string&, string);
std::vector<string> split (const string&, char);


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
    static Attribute make_from_dump(string& str);

protected:///Members
	bool m_is_root;
	QVariant* m_val;
	string m_name;
};

class DataKeeperTree
{
public:
    friend class TreeIterator;

	DataKeeperTree() noexcept;
	DataKeeperTree(const DataKeeperTree&) noexcept;
	DataKeeperTree(DataKeeperTree*) noexcept;
	DataKeeperTree(DataKeeperTree&&) noexcept;
    DataKeeperTree(Attribute&) noexcept;
    DataKeeperTree(Attribute, DataKeeperTree*)noexcept;
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

    ///ITERATOR FOR TREE
    class TreeIterator{
    public:
        using value_type        = DataKeeperTree;
        using pointer           = DataKeeperTree*;
        using reference         = DataKeeperTree&;

        TreeIterator(pointer = nullptr);

        pointer operator*() const;
        TreeIterator &operator++();
        bool operator!=(const pointer)const;
        bool operator!=(const TreeIterator&)const;
        bool operator==(const pointer)const;
        bool operator==(const TreeIterator&)const;

    private:
        pointer ptr;
        pointer prev_ptr;
    };

    TreeIterator begin();
    TreeIterator end();
    DataKeeperTree* at(const int i);
    DataKeeperTree* operator[](const int i);
private:
    void _getDump(DataKeeperTree*, string&);       ///recursive make dump from this elem
    static void _parseDumpLine(DataKeeperTree*, string&); ///convert from string dump

protected: ///Members
	Attribute m_atr;
	std::vector<DataKeeperTree*>* m_childs;
	DataKeeperTree* m_parent;
};

///Для работы с алгоритмами! Надо тестить!!!
namespace std {
template<>
struct iterator_traits<DataKeeperTree::TreeIterator>{
    using iterator_category = std::forward_iterator_tag;
    using value_type        = DataKeeperTree;
};
}
