#include "DataKeeperTree.h"
#define SEPORATOR std::string("/")
/*!
 * \todo
 * Сделать загрузку дампов и поиск по имени и атрибуту
 * Продумать обход дерева
 * Сделать граф интерфейс для примера на сервере и клиенте
 * Сделать функции отправки и приянтия дампов от клиента
 */

DataKeeperTree::DataKeeperTree() noexcept:
    m_atr(nullptr), m_childs(nullptr), m_parent(nullptr)
{
}

DataKeeperTree::DataKeeperTree(const DataKeeperTree& other) noexcept:
    m_atr(other.m_atr), m_childs(other.m_childs), m_parent(other.m_parent)
{
}

DataKeeperTree::DataKeeperTree(DataKeeperTree* other) noexcept:
    m_atr(other->m_atr), m_childs(other->m_childs), m_parent(other->m_parent)
{
	other->m_atr = nullptr;
	other->m_parent = nullptr;
	other->m_childs = nullptr;
	other = nullptr;
}

DataKeeperTree::DataKeeperTree(DataKeeperTree&& other) noexcept:
    m_atr(other.m_atr), m_childs(other.m_childs), m_parent(other.m_parent)
{
	other.m_atr = nullptr;
	other.m_parent = nullptr;
	other.m_childs = nullptr;
}

DataKeeperTree::DataKeeperTree(QVariant* val) noexcept:
    m_atr(val), m_childs(nullptr), m_parent(nullptr)
{
}

DataKeeperTree::DataKeeperTree(Attribute &attr) noexcept:
    m_atr(attr), m_childs(nullptr), m_parent(nullptr)
{}

DataKeeperTree::DataKeeperTree(QVariant* val, DataKeeperTree* parent) noexcept:
    m_atr(val), m_childs(nullptr), m_parent(parent)
{
	parent->push_child(this);
}

void DataKeeperTree::push_child(DataKeeperTree* elem)
{
	if (m_childs == nullptr) {
		m_childs = new std::vector<DataKeeperTree*>();
	}

    for(auto it:*m_childs)
        if(it==nullptr){
            it=elem;
            elem->m_parent=this;
        }

    if(elem->m_parent!=this){
        m_childs->push_back(elem);
        elem->m_parent = this;
    }
}

void DataKeeperTree::pop_child()
{
    if(m_childs != nullptr)
        m_childs->pop_back(); ///check next func if worry about memory
}

void DataKeeperTree::erase_elem(DataKeeperTree *elem)
{
    if(elem==nullptr) return;

    auto vect_ptr = elem->m_parent->m_childs; ///pointer to parent child's vector

    auto it = std::find(vect_ptr->begin(), vect_ptr->end(), elem);
    if(it!=vect_ptr->end()){
        const auto new_end (std::remove(vect_ptr->begin(),vect_ptr->end(),it));
        vect_ptr->erase(new_end, vect_ptr->end()); ///in erase use deallocate() and destroy(), all right ;)
        elem=nullptr;
    }
}

DataKeeperTree *DataKeeperTree::get_parent()
{
    return m_parent;
}

void DataKeeperTree::del_all_child(DataKeeperTree* branch)
{
    for(auto it : *branch->m_childs)
        del_all_child(it);
    if(m_childs!=nullptr) m_childs->clear();
}

size_t DataKeeperTree::childs_count()
{
    return (m_childs != nullptr) ? m_childs->size() : 0;
}

DataKeeperTree *DataKeeperTree::find_by_attr(DataKeeperTree *root, Attribute &attr)
{

}

DataKeeperTree *DataKeeperTree::find_by_name(DataKeeperTree *root, std::string &name)
{

}

DataKeeperTree *DataKeeperTree::find_root()
{
    DataKeeperTree* ptr = this;
    while(!ptr->is_root() && ptr->has_parent()){
        ptr = ptr->m_parent;
    }
    if(ptr->is_root()) return ptr;
    return nullptr;
}

bool DataKeeperTree::is_root()
{
	return m_atr.is_root();
}

bool DataKeeperTree::has_parent()
{
	return m_parent != nullptr;
}

bool DataKeeperTree::has_childs()
{
	return m_childs != nullptr;
}

bool DataKeeperTree::has_attribute()
{
    return m_atr.is_valid();
}

bool DataKeeperTree::has_name()
{
    return (m_atr.is_valid() && !m_atr.get_name().empty());
}

string DataKeeperTree::get_dump(DataKeeperTree* branch)
{
    std::string dump_str;
    _getDump(branch, dump_str);
    return dump_str;
}

DataKeeperTree* DataKeeperTree::from_dump(string& dump_str)
{
    return nullptr;
}

//!
//! \brief DataKeeperTree::_getDump - service func for recursive getting dump of tree
//! \param parent - for call all children and return litlle dump string
//! \param str - one string of all tree, recursive trow like link
//!
void DataKeeperTree::_getDump(DataKeeperTree* parent , std::string &str)
{
    if(parent!=nullptr){
        if(parent->m_childs!=nullptr && !m_childs->empty())
            for(auto it: *parent->m_childs){ ///call all childes
                _getDump(it ,str+=parent->m_atr.make_dump_string()); ///recurive call for write new elem to str
            }
        else
            str+=parent->m_atr.make_dump_string()+"\n";
    }
}

//!
//! \brief DataKeeperTree::_parseDump - get a line from dump and pars to DataKeeper structure
//!
void DataKeeperTree::_parseDumpLine(DataKeeperTree *root, std::string &line)
{

}

DataKeeperTree::~DataKeeperTree()
{
	for (auto it : *m_childs)
		delete it;
	delete m_childs;
}

Attribute::Attribute() noexcept:
    m_is_root(true), m_val(nullptr)
{
}

Attribute::Attribute(QVariant* val) noexcept:
    m_is_root(false), m_val(val)
{
}

Attribute::Attribute(std::string &name) noexcept:
    m_is_root(false), m_val(nullptr), m_name(name)
{
}

Attribute::Attribute(QVariant* val, const string& name) noexcept:
    m_is_root(false), m_val(val), m_name(name)
{
}

Attribute::~Attribute()
{
    if (m_val != nullptr)
		delete m_val;
}

bool Attribute::is_root()
{
	return m_is_root;
}

bool Attribute::is_valid()
{
	return m_val!=nullptr;
}

const string& Attribute::get_name()
{
	return this->m_name;
}

QVariant* Attribute::get_val()
{
    return m_val;
}

std::string Attribute::make_dump_string()
{
    std::string dump_str = SEPORATOR;

    if(is_root())   dump_str+="root";
    if(!m_name.empty()) is_root() ? dump_str += "," + m_name : dump_str += m_name;
    if(is_valid())  (!m_name.empty()||is_root())?
            dump_str += "," + get_val()->toString().toStdString():
            dump_str += get_val()->toString().toStdString();

    return dump_str;
}

bool Attribute::operator!=(const Attribute &other)
{
    return !(*this==other);
}

bool Attribute::operator==(const Attribute &other)
{
    return m_name==other.m_name && m_is_root==other.m_is_root;
}

Attribute Attribute::make_from_dump(std::string &str)
{

}
