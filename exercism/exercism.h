#if !defined(EXERCISM_H)
#define EXERCISM_H
#include <memory>
// #include <utility>
#include <iterator>

using namespace std;
namespace binary_search_tree {
    
    template <typename T>
    class binary_tree{
      private:
        T value;
        binary_tree<T>* lPtr;
        binary_tree<T>* rPtr;
        binary_tree<T>* parent;
        bool visited;
      public:
        struct Iterator{
            using iterator_category = input_iterator_tag;
            using difference_type = ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

            Iterator(pointer ptr, binary_tree<T>* owner): m_ptr(ptr), m_owner(owner){
                if(owner) owner->visited=true;}
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }; 
            friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }; 
            pointer operator->() { return m_ptr; }
            reference operator*() const { return *m_ptr; }
            Iterator& operator++() {
                if(m_owner->rPtr!=nullptr){
                    binary_tree<T>* p = m_owner->rPtr;
                    while(p->lPtr){
                        p = p->lPtr;
                    }
                    m_ptr = &p->value;
                    m_owner = p;}
                else if(m_owner->parent==nullptr){
                    m_ptr = nullptr;}
                else if(m_owner->parent->visited){
                    binary_tree<T>* p = m_owner->parent;
                    while(p->visited){
                        if(p->parent==nullptr){
                            m_ptr = nullptr;
                            m_owner = nullptr;
                            return *this;
                        }
                        else p = p->parent;
                    }
                    m_ptr = &p->value;
                    m_owner = p;}
                else{
                    m_ptr = &m_owner->parent->value;
                    m_owner = m_owner->parent;}
                m_owner->visited = true;
                return *this;
            }  
                        
            private:
              pointer m_ptr;
              binary_tree<T>* m_owner;
        };

        Iterator begin(){
            if(this->lPtr==nullptr) return Iterator(&value, this);
            else return this->lPtr->begin(); }

        Iterator end(){ return Iterator(nullptr, nullptr);}

        binary_tree(const T &item){
            this->value = item;
            this->lPtr =nullptr;
            this->rPtr =nullptr;
            this->visited = false;
            this->parent =nullptr;
        };

        T data() const{
            return this->value;
        };

        void insert(const T &item){ 
            if(item <= this->value){
                if(this->lPtr) this->lPtr->insert(item);
                else{
                    this->lPtr = new binary_tree<T>(item);
                    this->lPtr->parent = this;}
            }else{
                if(this->rPtr) this->rPtr->insert(item);
                else{
                    this->rPtr = new binary_tree<T>(item);
                    this->rPtr->parent = this;}
            }
        };

        unique_ptr<binary_tree<T>> left() const{
            return this->lPtr != nullptr ? make_unique<binary_tree<T>>(*(this->lPtr)) : nullptr;;
        };

        unique_ptr<binary_tree<T>> right() const{
            return this->rPtr != nullptr ? make_unique<binary_tree<T>>(*(this->rPtr)) : nullptr;
        };
    };
}  // namespace binary_search_tree

#endif // EXERCISM_H