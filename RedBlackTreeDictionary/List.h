// ordered singly linked list for string type inputs 
#ifndef LIST_H
#define LIST_H

#include <fstream>
#include <string>

class List
{
public:

    List() : 
        head_(nullptr), 
        tail_(nullptr), 
        count_(0) 
    {}
    List(std::string meaning);
    ~List();
    
    List(const List& src) = delete;
    List(List&& src) noexcept = delete;
    List& operator=(const List& src) = delete;
    List& operator=(List&& src) noexcept = delete;
    
    int getCount() const;
    bool insertItem(const std::string& meaning);
    void print(std::ostream& out);
    std::string getFirstItem() const
    {
        if (head_ == nullptr) {
            
            
            return " "; 
        }

        return head_->meaning_;
    }
private:
    struct Node
    {
        std::string meaning_;
        Node* next_;
        Node(std::string meaning, Node* next = nullptr) :
            meaning_(meaning), 
            next_(next)
        {};
    };
 
    int count_;
    Node* head_;
    Node* tail_;
};



#endif // !LIST_H
