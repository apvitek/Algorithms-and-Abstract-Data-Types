// List.java
// Andrea Vitek
// 1559060
// pa 1
// This file contains the implementation of the List ADT

public class List {
	// Internal Node class
	private class Node {
		// Instance Variables
		int data;
		Node next, prev;

		// Constructor
		Node(int data) {
			this.data = data;
			next = prev = null;
		}
		
		// Overridden Methods
		public String toString() {
			return String.valueOf(data);
		}
	}

	// Instance Variables
	private Node front, back, cursor;
	private int length, index;

	// Constructor
	List() {
		front = back = cursor = null;
		length = 0;
		index = -1;
	}

	// ACCESS FUNCTIONS

	// Returns front element
	// Pre: !this.isEmpty()
	public int front() {
		if (!this.isEmpty()) {
			return front.data;
		} else {
			throw new RuntimeException("List Error: getFront() called on empty List");
		}
	}

	// Returns back element
	// Pre: !this.isEmpty()
	public int back() {
		if (!this.isEmpty()) {
			return back.data;
		} else {
			throw new RuntimeException("List Error: getBack() called on empty List");
		}
	}

	// Returns cursor element
	// Pre: length()>0, index>=0
	public int get() {
		if (this.isEmpty() || index < 0) {
			throw new RuntimeException("List Error: get() called on undefined cursor");
		}

		return cursor.data;
	}

	// Returns length of list
	public int length() {
		return length;
	}

	public boolean isEmpty() {
		return this.length == 0;
	}

	// If cursor is defined, returns the index of the cursor element, otherwise returns -1.
	public int index() {
		return index;
	}
	
	// Return a truth value of whether two Lists are the same
	public boolean equals(List otherList) {
		if (this.isEmpty() && otherList.isEmpty()) {
			return true;
		} else if (this.length() != otherList.length()) {
			return false;
		} else {
			int previousIndex = otherList.index(); // Save otherList's index
			otherList.moveFront();
			
			Node currentNode = front;

			while (currentNode != null) {
				if (currentNode.data != otherList.get()) {
					otherList.setIndex(previousIndex); // Restore otherList's index
					return false;
				}
				
				otherList.moveNext();
				currentNode = currentNode.next;
			}
			
			otherList.setIndex(previousIndex); // Restore otherList's index
			return true;
		}
	}

	// MANIPULATION PROCEDURES

	// Resets this List to its original empty state.
	public void clear() {
		if (back != null) {
			// Necessary for the Garbage Collector to delete the nodes, can't simply set back/front/cursor to null
			// Otherwise, they nodes keep a reference to each other and do not get deallocated.
			while (back.prev != null) {
				back.prev.next = null;
				back = back.prev;
			}

			back = front = cursor = null;
			length = 0;
		}
	}

	// If List is non-empty, places the cursor under the front element, otherwise does nothing.
	public void moveFront() {
		if (!this.isEmpty()) {
			cursor = this.front;
			index = 0;
		}
	}

	// If List is non-empty, places the cursor under the back element, otherwise does nothing.
	public void moveBack() {
		if (!this.isEmpty()) {
			cursor = this.back;
			index = length - 1;
		}
	}

	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	public void movePrev() {
		if (index >= 0) {
			cursor = cursor.prev;
			index--;
		}
	}

	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	public void moveNext() {
		if (index >= 0) {
			if (index == length - 1) {
				index = -1;
			} else {
				cursor = cursor.next;
				index++;
			}
		} 
	}

	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	public void insertBefore(int data) {
		if (this.isEmpty() || index < 0) {
			throw new RuntimeException("List Error: insertBefore() called on undefined cursor or empty list");
		}

		if (cursor == front) {
			this.prepend(data);
		} else {
			Node newNode = new Node(data);
			newNode.prev = cursor.prev;
			newNode.next = cursor;
			newNode.prev.next = newNode;
			cursor.prev = newNode;
			length++;
			index++;
		}
	}

	// Insert new element after cursor.
	// Pre: length()>0, index()>=0
	public void insertAfter(int data) {
		if (this.isEmpty() || index < 0) {
			throw new RuntimeException("List Error: insertBefore() called on undefined cursor or empty list");
		}

		if (cursor == back) {
			this.append(data);
		} else {
			Node newNode = new Node(data);
			newNode.next = cursor.next;
			newNode.prev = cursor;
			newNode.next.prev = newNode;
			cursor.next = newNode;
			length++;
		}
	}

	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	public void delete() {
		if (this.isEmpty() || index < 0) {
			throw new RuntimeException("List Error: delete() called on undefined cursor");
		}

		if (cursor == front) {
			this.deleteFront();
		} else if (cursor == back) {
			this.deleteBack();
		} else {
			cursor.prev.next = cursor.next;
			cursor.next.prev = cursor.prev;
			cursor = null;
			length--;
		}
	}

	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	public List copy() {
		List copiedList = new List();

		if (!this.isEmpty()) {
			Node currentNode = front;

			while (currentNode != null) {
				copiedList.append(currentNode.data);
				currentNode = currentNode.next;
			}
		}

		return copiedList;
	}

	// Returns a new List which is the concatenation of
	// this list followed by L. The cursor in the new List
	// is undefined, regardless of the states of the cursors
	// in this List and L. The states of this List and L are
	// unchanged.
	public List concat(List otherList) {
		List newList = this.copy();

		if (otherList.isEmpty()) {
			return newList;
		}

		int previousIndex = otherList.index();

		otherList.moveFront();

		while (otherList.index() != -1) {
			newList.append(otherList.cursor.data);
			otherList.moveNext();
		}
		
		// Restore cursor in otherList
		otherList.setIndex(previousIndex);

		return newList;
	}

	// Appends data to back of this Queue.
	public void append(int data) {
		Node newNode = new Node(data);

		if (this.isEmpty()) {
			front = back = newNode;
		} else {
			newNode.prev = back;
			back.next = newNode; 
			back = newNode;
		}

		length++;
	}

	// Insert new element into this List. If List is non-empty, insertion takes place before front element.
	public void prepend(int data) {
		Node newNode = new Node (data);

		if (!this.isEmpty()) {
			front.prev = newNode;
			newNode.next = front;
			front = newNode;
		} else {
			newNode.next = newNode.prev = null;
			front = back = newNode;
		}

		length++;
		index++;
	}

	// Deletes the front element.
	// Pre: length()>0
	public void deleteFront() {
		if (this.isEmpty()) {
			throw new RuntimeException("List Error: deleteFront() called on empty List");
		}

		if (cursor == front) {
			cursor = null;
			index = -1;
		}

		if (this.length > 1) {
			front.next.prev = null;
			front = front.next;
		} else {
			front = back = null;
		}

		length--;
		
		if (index != -1) {
			index--;
		}
	}

	// Deletes the back element.
	// Pre: length()>0
	public void deleteBack() {
		if (this.isEmpty()) {
			throw new RuntimeException("List Error: deleteBack() called on empty List");
		}

		if (cursor == back) {
			cursor = null;
			index = -1;
		}

		if (this.length > 1) {
			back.prev.next = null;
			back = back.prev;
		} else {
			front = back = null;
		}

		length--;
	}

	// OVERRIDDEN METHODS
	
	// Prints the elements in the List in an orderly fashion
	public String toString() {
		if (this.isEmpty()) {
			return "<Empty List>";
		}

		StringBuffer sb = new StringBuffer();
		Node currentNode = front;

		while (currentNode != null) {
			sb.append(" ");
			sb.append(currentNode.toString());
			currentNode = currentNode.next;
		}

		return new String(sb);
	}
	
	// ACCESSORY METHODS
	
	// Restores an index in a list
	private void setIndex(int index) {
		if (index != -1) {
			this.moveFront();
			
			while(this.index() != index) {
				this.moveNext();
			}
		}
	}
}