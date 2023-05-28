#include"List.h"

#include <iostream>
//#include <utility>


List::List(std::string meaning) :
    count_(1)
{
    head_ = tail_ = new Node(meaning);
}

List::~List()
{

    Node* current = nullptr;
    Node* next = head_;
    while (next != nullptr)
    {
        current = next;
        next = next->next_;
        delete current;
    }
    tail_ = nullptr;
    head_ = nullptr;
}

int List::getCount() const
{
    return count_;
}

bool List::insertItem(const std::string& meaning)
{
    Node* previous = nullptr;
    Node* current = head_;
    if (!current)
    {
        head_ = tail_ = new Node(meaning);
        count_++;
        return true;
    }
    while (current != nullptr)
    {
        if (meaning == current->meaning_)
        {
            return false;
        }
        if (meaning > current->meaning_)
        {
            previous = current;
            current = current->next_;
        }
        else
        {
            if (previous)
            {
                previous->next_ = new Node(meaning, current);
                count_++;
                return true;
            }
            else
            {
                head_ = new Node(meaning, current);
                count_++;
                return true;
            }
        }
    }
    tail_ = previous->next_ = new Node(meaning);
    count_++;
    return true;
}

void List::print(std::ostream& out)
{
    Node* current = head_;
    if (!current)
    {
        out << "List is empty\n";
        return;
    }
    while (current)
    {
        out << " - " << current->meaning_ << '\n';
        current = current->next_;
    }
}