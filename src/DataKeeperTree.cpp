#include "DataKeeperTree.h"
#define SEPORATOR std::string("/")
/*!
 * \todo
 * 1) Написать тесты и отладить
 * 2) Сделать граф интерфейс для примера на сервере и клиенте
 * 3) Сделать функции отправки и приянтия дампов от клиента
 !*/

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

DataKeeperTree::DataKeeperTree(Attribute attr, DataKeeperTree *parent) noexcept:
    m_atr(attr), m_childs(nullptr), m_parent(parent)
{
    m_parent->push_child(this);
}

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
    static DataKeeperTree* sought = nullptr;
    if(sought==nullptr){
        if(root->m_atr!=attr)
            for(auto it: *root->m_childs)
                find_by_attr(it, attr);
        else
            sought = root;
    }
    return sought;
}

DataKeeperTree *DataKeeperTree::find_by_name(DataKeeperTree *root, std::string &name)
{
    static DataKeeperTree* sought = nullptr;
    if(sought==nullptr){
        if(root->m_atr.get_name()!=name)
            for(auto it: *root->m_childs)
                find_by_name(it, name);
        else
            sought = root;
    }
    return sought;
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
    if(branch!=nullptr){
        std::string dump_str;
        _getDump(branch, dump_str);
        return dump_str;
    }
    else return std::string();
}

//!
//! \brief DataKeeperTree::from_dump
//! \param dump_str
//! \return if dump_str empty return nullptr else return root elem of new Tree
//!
DataKeeperTree* DataKeeperTree::from_dump(string& dump_str)
{
    if(!dump_str.empty()){
        auto str_vect = split(dump_str,'\n');
        DataKeeperTree* root = new DataKeeperTree(); ///Make root element
        for(auto it: str_vect)                       ///And parse all string from dump
            _parseDumpLine(root, it);
        return root;
    }
    else{
        return nullptr;
    }
}

DataKeeperTree *DataKeeperTree::at(const size_t i)
{
    if(i>=m_childs->size()) return nullptr;
    else return m_childs->at(i);
}

DataKeeperTree *DataKeeperTree::operator[](const int i)
{
    return m_childs->at(i);
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
    if(line.empty()) return;
    if(root==nullptr) return;
    auto str_vect = split(line, SEPORATOR);
    auto temp_branch = root;
    for(auto it:str_vect){
        auto new_attr = Attribute::make_from_dump(it);
        DataKeeperTree branch(new_attr);
        if(new_attr.is_root()){
            continue;
        }
        else{
            auto elem = std::find(temp_branch->m_childs->begin(),temp_branch->m_childs->end(), new_attr);
            if(elem!=temp_branch->m_childs->end()){
                root = *elem;
            }
            else{
                root = new DataKeeperTree(new_attr, root);
            }
        }
    }
}

DataKeeperTree::~DataKeeperTree()
{
	for (auto it : *m_childs)
		delete it;
    delete m_childs;
}

bool DataKeeperTree::operator==(const DataKeeperTree &other)
{
    return this->m_atr==other.m_atr;
}

bool DataKeeperTree::operator==(const Attribute &attr)
{
    return this->m_atr==attr;
}

bool DataKeeperTree::operator!=(const DataKeeperTree &other)
{
    return this->m_atr!=other.m_atr;
}

bool DataKeeperTree::operator!=(const Attribute &attr)
{
    return this->m_atr!=attr;
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
    else is_root() ? dump_str += "," + generate_name() : dump_str += generate_name(); ///generate name if has not

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
    auto vec = split(str,',');
    Attribute attr;
    attr.m_is_root = false;
    if(vec.size()!=0){
        if(vec.size()==1){
            if(vec[0]=="root") attr.m_is_root = true;
            else attr.set_name(vec[0]);
        }
        else if(vec.size()==2){
            if(vec[0]=="root") {
                attr.m_is_root = true;
                attr.set_name(vec[1]);
            }
            else{
                attr.m_name=vec[0];
                attr.m_val = new QVariant(QString::fromStdString(vec[1]));
            }
        }
        else if(vec.size()==3){
            attr.m_is_root = true;
            attr.set_name(vec[1]);
            attr.m_val = new QVariant(QString::fromStdString(vec[1]));
        }
    }
    return attr;
}

bool Attribute::set_name(std::string &str)
{
    if(str.find("GeneratedName_")!=std::string::npos){
        return false;
    }
    else{
        this->m_name = str;
        return true;
    }
    return false;
}

std::string Attribute::generate_name()
{
    static int name_numb = 0;
    std::string str = "GeneratedName_";
    str += std::to_string(name_numb);
    ++name_numb;
    return str;
}

std::vector<std::string> split(const std::string &s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    std::vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<string> result;
    std::stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

DataKeeperTree::TreeIterator::TreeIterator(DataKeeperTree::TreeIterator::pointer point): ptr(point), prev_ptr(nullptr)
{}

DataKeeperTree::TreeIterator::pointer DataKeeperTree::TreeIterator::operator*() const
{
    return this->ptr;
}

///Надо тестить
DataKeeperTree::TreeIterator &DataKeeperTree::TreeIterator::operator++()
{
    if(ptr->has_childs() && ptr->childs_count()!=0){
        ptr = ptr->m_childs->at(0);
    }
    else{
        auto parent_ptr = ptr->m_parent;
        auto vec_ptr = ptr->m_parent->m_childs;
        auto it = std::find(vec_ptr->begin(), vec_ptr->end(), ptr);
        if(it!=vec_ptr->end()){
            while (*it == vec_ptr->at(vec_ptr->size())) { ///Если мы последний элемент у данного верктора
                parent_ptr = (*it)->m_parent;
                vec_ptr = parent_ptr->m_parent->m_childs;
                it = std::find(vec_ptr->begin(), vec_ptr->end(), parent_ptr);
                if(it==vec_ptr->end()) {
                    throw std::out_of_range("Error! Not found preious element in children vector");
                    return *this;
                }
            }
            if(*it != vec_ptr->at(vec_ptr->size())){
                ptr = *(++it); ///next elem in vect
            }
            else{
                throw std::out_of_range("Error! Not found preious element in children vector");
                return *this;
            }
        }
        else{
            throw std::out_of_range("Error! Not found preious element in children vector");
            return *this; ///Возвращаем старый указатель если не нашли !!!Но лучше исключение
        }
    }
    return *this;
}

bool DataKeeperTree::TreeIterator::operator!=(const DataKeeperTree::TreeIterator::pointer other) const
{
    return ptr != other;
}

bool DataKeeperTree::TreeIterator::operator==(const DataKeeperTree::TreeIterator::pointer other) const
{
    return ptr == other;
}

bool DataKeeperTree::TreeIterator::operator!=(const DataKeeperTree::TreeIterator& other) const
{
    return ptr != other.ptr;
}

bool DataKeeperTree::TreeIterator::operator==(const DataKeeperTree::TreeIterator& other) const
{
    return ptr == other.ptr;
}
