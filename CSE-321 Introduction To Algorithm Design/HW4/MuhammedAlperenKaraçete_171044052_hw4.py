#!/usr/bin/env python
# coding: utf-8

# In[10]:


import random
def partition(array, startPos, endPos) :
 
    pivot = array[endPos]
    i = (startPos - 1)
    for j in range(startPos, endPos) :
        if array[j] <= pivot :
            i += 1
            array[i], array[j] = array[j], array[i]
         
    array[i + 1], array[endPos] = array[endPos], array[i + 1]
    return (i + 1)
 
# Implementation of QuickSelect
def findkthSmallestElement(array, startPos, lengthOfArray, middleElement) :
 
    while startPos <= lengthOfArray :
 
       
        #find the position of the pivot
        pivotIndex = partition(array, startPos, lengthOfArray)
 
        # If pivot itself is the k-th smallest element
        if pivotIndex == middleElement - 1 :
            return array[pivotIndex]
 
        # If there are more than k-1 elements on left of pivot, then k-th smallest must be on left side.
        elif pivotIndex >middleElement - 1 :
            lengthOfArray = pivotIndex - 1
 
        # Else k-th smallest is on right side.
        else :
            startPos = pivotIndex + 1
     
    return -1


# In[11]:


class Node:
    def __init__(self, playerNo):
        self.playerNo = playerNo
        self.next = None

def create_linked_list(length):
  # Create nodes for each player
    head = Node(1)
    prev = head
    for i in range(2, length + 1):
        prev.next = Node(i)
        prev = prev.next
    prev.next = head
    return head

def find_winner(head,length):
  # Initialize pointer to head of linked list
    survivorPos = 0
    for i in range(1, length+1):
        survivorPos = (survivorPos + 2) % i #With this code I found position of the winner on linear time.
    tempHead = head
    for i in range(survivorPos):
        tempHead = tempHead.next #Then I took head on tempHead and go next on Temphead until iterate the winner position.
    return tempHead.playerNo #Then return winner.


# In[12]:


def findWinner(lengthOfCircle):
      
    playersIncludedWithDeads = 1
    while playersIncludedWithDeads <= lengthOfCircle:
        playersIncludedWithDeads = 2 * playersIncludedWithDeads #Founds minimum power of 2 that is smaller than count of players in circle.
  
    return ((2 * lengthOfCircle) - playersIncludedWithDeads) + 1 #With this code I found position of the winner.We multiply player size with 2 because, 2 represents how many player is skipping before selecting next survivor.
  


# In[13]:


def driverFunction():

    print ("Part2")
    array = []
    lengthOfArray=5 #Enter length of array here
    for i in range(lengthOfArray):
        array.append(random.randint(1, 100))
    lengthOfArray = len(array)-1
    middlePosition = lengthOfArray//2+1
    print("Median element",findkthSmallestElement(array, 0, lengthOfArray, middlePosition))
    print("******************************************************************************")
    
    print ("Part3 a")
    lengthOfCircleA = 5 #Enter size of player here
    head = create_linked_list(lengthOfCircleA)
    result = find_winner(head,lengthOfCircleA)
    print("The winner is number:",result)  
    print ("in this count of people:",lengthOfCircleA)
    print("******************************************************************************")    
    
    print ("Part3 b")
    lengthOfCircleB = 5 #Enter size of player here
    print ("The winner is number:", findWinner(lengthOfCircleB))
    print ("in this count of people:",lengthOfCircleB)    
driverFunction()


# In[ ]:




