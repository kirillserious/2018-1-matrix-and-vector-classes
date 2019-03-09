#ifndef DICTIONARY_H_
#define DICTIONARY_H_
namespace vika_lib {

template <typename Key, typename Value>
class Dictionary_element;

template <typename Key, typename Value>
class Dictionary
{
private:
    struct Node
    {
        Key key;
        Value value;
        Node *next;
        Node *prev;

        Node (): next(nullptr), prev(nullptr){}
    };

    Node *_list;

    //Добавляет элемент
    void
    insert_node (const Key &key, const Value &value)
    {
        if (_list == nullptr) {
            _list        = new Node;
            _list->key   = key;
            _list->value = value;
        } else {
            Node *tmp = _list;
            while (tmp->next != nullptr) {
                tmp = tmp->next;
            }
            tmp->next = new Node;
            tmp->next->key = key;
            tmp->next->value = value;
            tmp->next->prev  = tmp;
        }
    }

    //Поиск структуры элемента по ключу
    Node*
    search_node (const Key &key) const
    {
        if (_list == nullptr) return nullptr;

        Node *tmp = _list;
        while ((tmp->key != key) && (tmp->next != nullptr)) {
            tmp = tmp->next;
        }

        return (tmp->key == key) ? tmp : nullptr;
    }

    //Удаляет элемент
    void
    remove_node (Node *node)
    {
        if ((node->prev == nullptr) && (node->next == nullptr)) {
            delete _list;
            _list = nullptr;
            return;
        }

        if (node->prev == nullptr) {
            _list = node->next;
            delete node;
            return;
        }

        if (node->next == nullptr) {
            node->prev = nullptr;
            delete node;
            return;
        }

        node->next->prev = node->prev;
        node->prev->next = node->next;
        delete node;
        return;
    }

    //Освобождает память от списка
    void
    remove_list ()
    {
        if (_list == nullptr){
            return;
        }

        while (_list->next != nullptr) {
            _list = _list->next;
            delete _list->prev;
        }

        delete _list;
        _list = nullptr;
    }

    //Выдает копию _list
    Node*
    copy_list () const
    {
        if (_list == nullptr){
            return nullptr;
        }
        
        Node *res, *tmp;
        
        res = new Node;
        res->key = _list->key;
        res->value = _list->value;

        Node *result = res;
        tmp = _list;
        while (tmp->next != nullptr) {
            res->next = new Node;
            res->next->prev = res;
            res->next->key = tmp->next->key;
            res->next->value = tmp->next->value;
            res = res->next;
            tmp = tmp->next;
        }

        return result;
    }
//////////////////////////////////////
    int *_link_counter;

//////////////////////////////////////

    

    enum { NO_VALUE = 0 };

/////////////////////////////////////
    friend class Dictionary_element<Key, Value>;

    Value
    get (const Key &key) const
    {
        Node *node = search_node(key);
        if (node != nullptr) {
            return node->value;
        } else {
            return NO_VALUE;
        }
    }

    void
    set (const Key &key, const Value &value)
    {
        if (*_link_counter > 1) {
            (*_link_counter)--;
            _list = copy_list();
            _link_counter = new int;
            (*_link_counter) = 1;
        }

        Node *node = search_node(key);

        if ((node == nullptr) && (value == NO_VALUE)) return;
        if (node == nullptr) {
            insert_node(key, value);
            return;
        }
        if (value == NO_VALUE) {
            remove_node(node);
            return;
        }

        node->value = value;
    }

public:
    typedef Dictionary_element<Key, Value> Element;

    Dictionary () :
    _list(nullptr)
    {
        _link_counter  = new int;
        *_link_counter = 1;
    }

    Dictionary (const Dictionary &dict):
    _list (dict._list), _link_counter (dict._link_counter)
    {
        (*_link_counter)++;
    }

    Dictionary &
    operator = (const Dictionary &dict)
    {
        if (*_link_counter > 1) {
            (*_link_counter)--;
        } else {
            remove_list();
            delete _link_counter;
        }

        _list = dict._list;
        _link_counter = dict._link_counter;
        (*_link_counter)++;
    }

    ~Dictionary ()
    {
        if (*_link_counter > 1) {
            (*_link_counter)--;
        } else {
            remove_list();
            delete _link_counter;
        }
    }

    Element
    operator ()(Key key)
    {   
        return Element(this, key);
    }

    inline
    Value
    operator[] (const Key &key) const
    {
        return get(key);
    }


};

template <typename Key, typename Value>
class Dictionary_element
    {
    friend class Dictionary<Key, Value>;

    private:
        Dictionary<Key, Value> *_dict;
        Key _key;
    
        Dictionary_element (Dictionary<Key, Value> *dict, const Key &key) :
        _dict (dict), _key (key)
        {}

    public:
        Dictionary_element &
        operator= (const Value &value)
        {
            _dict->set(_key, value);
        }

        operator Value () const
        {
            return _dict->get(_key);
        }
    };
}
#endif