//John Vande Noord and Claire Ujeneza


#include "ListLinked.h"

template <typename DataType>
List<DataType>::List(int ignored){
	head=NULL;
	cursor=NULL;
}


// Copy constructor. Creates a list which is equivalent in content
// to the "other" list.
template <typename DataType>
List<DataType>::List(const List& other)
: head(0), cursor(0)
  {
	operator=(other);
  }


// Overloaded assignment operator. Reinitializes the list to be
// equivalent in content to the "other" list.
// Note: we include self-assignment protection by checking whether
// "this" object is identical to the "other" object.
template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
{
	if( this != &other ) {
		clear();
		ListNode *otherPtr = other.head;
		ListNode *holdCursor = 0;
		while( otherPtr != 0 ) {
			insert(otherPtr->dataItem);
			if(otherPtr == other.cursor) {
				holdCursor = cursor;
			}
			otherPtr = otherPtr->next;
		}
		cursor = holdCursor;
	}

	return *this;
}


// Destructor. Frees the memory used by a list.
template <typename DataType>
List<DataType>::~List()
{
	clear();
}

template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr){
	dataItem=nodeData;
	next=nextPtr;
}

template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error){
	if(!isEmpty()){
		if(cursor->next==NULL){
			cursor->next=new ListNode(newDataItem,NULL);
			cursor=cursor->next;
		}else{
			cursor->next=new ListNode(newDataItem,cursor->next);
			cursor=cursor->next;
		}
	}else{
		head=new ListNode(newDataItem, NULL);
		cursor=head;
	}
}

template <typename DataType>
void List<DataType>::remove() throw (logic_error){
	if(head==NULL)
		throw logic_error("No data");
	if(cursor==head){
		ListNode* temp=head;
		head=head->next;
		cursor=head;
		delete temp;
	}else{
		ListNode* temp=cursor->next;
		ListNode* temp2=cursor;
		this->gotoPrior();
		cursor->next=temp;
		cursor=temp;
		delete temp2;
	}
}

template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error){
	if(head==NULL)
		throw logic_error("No data");
	cursor->dataItem=newDataItem;
}

template <typename DataType>
void List<DataType>::clear(){
	cursor=head;
	do{
		delete cursor;
	}while(this->gotoNext());
	head=NULL;
	cursor=NULL;
}

template <typename DataType>
bool List<DataType>::isEmpty() const{
	return head==NULL;
}

template <typename DataType>
bool List<DataType>::isFull() const{
	return true;
}

template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error){
	if(head==NULL)
		throw logic_error("No data");
	cursor=head;
}

template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error){
	if(head==NULL)
		throw logic_error("No data");
	while(this->gotoNext()){}
}

template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error){
	if(head==NULL)
		throw logic_error("No data");
	if(cursor->next==NULL)
		return false;
	else{
		cursor=cursor->next;
		return true;
	}
}
template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error){
	if(head==NULL)
		throw logic_error("No data");
	if(cursor==head)
		return false;
	else if(head->next==cursor){
		cursor=head;
		return true;
	}else{
		ListNode* temp=cursor;
		cursor=head;
		while(this->gotoNext()&&cursor->next!=temp){}
		return true;
	}
}

template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error){
	if(head==NULL)
		throw logic_error("No data");
	return cursor->dataItem;
}
//--------------------------------------------------------------------
// show5.cpp: includes implementation of showStructure
//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
	if ( isEmpty() )
	{
		cout << "Empty list" << endl;
	}
	else
	{
		for (ListNode* temp = head; temp != 0; temp = temp->next) {
			if (temp == cursor) {
				cout << "[";
			}

			// Assumes that dataItem can be printed via << because
			// is is either primitive or operator<< is overloaded.
			cout << temp->dataItem;

			if (temp == cursor) {
				cout << "]";
			}
			cout << " ";
		}
		cout << endl;
	}
}







