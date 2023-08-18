class FullQueue
{};  

class EmptyQueue
{};  
typedef char ItemType;
class QueType
{
public: 
    QueType();
    // Class constructor.
    // Because there is a default constructor, the precondition 
    // that the queue has been initialized is omitted.
    QueType(int max);
    // Parameterized class constructor.
    ~QueType();
    // Class destructor.
    void MakeEmpty();
    // Function: Initializes the queue to an empty state.
    bool IsEmpty() const;
    // Function: Determines whether the queue is empty.
    bool IsFull() const;
    // Function: Determines whether the queue is full.
    void Enqueue(ItemType newItem);
    // Function: Adds newItem to the rear of the queue.
    void Dequeue(ItemType& item);
    // Function: Removes front item from the queue and returns it in item.
private:
    int front;
    int rear;
    ItemType* items;
    int maxQue;
};


