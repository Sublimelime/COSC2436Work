#include "BSTree.h"
#include "BSTNode.h"
#include <string>


BSTree::BSTree()
{
  rootNode = nullptr;
}

void deconstructHelper(BSTNode* node)
{
  if (node) {
    deconstructHelper(node->getLeftChild());
    deconstructHelper(node->getRightChild());
    delete node;
  }
}

BSTree::~BSTree()
{
  //implement destructor
  deconstructHelper(rootNode);
  rootNode = nullptr;
}

int countHeight(BSTNode *start)
{
  if (nullptr == start)
    {
      return -1;
    }
  else
    {
      int ld = countHeight(start->getLeftChild());
      int rd = countHeight(start->getRightChild());

      return max(ld, rd) + 1;
    }

}


int BSTree::getHeight() const
{
  return countHeight(rootNode);
}


int countNodes(BSTNode* start)
{
  if (nullptr == start)
    {
      return 0;
    }
  else
    {
      return 1 + countNodes(start->getLeftChild()) + countNodes(start->getRightChild());
    }
}

int BSTree::getNumNodes() const
{
  return countNodes(rootNode);
}

void representationHelper(string& result, BSTNode* current, string& path) {
  if (result == "") {
    result = ">" + current->getKey();
  } else {
    result += "\n" + path + current->getKey();
  }
  //left side
  if (current->getLeftChild()) {
    string temp = path + "l>";
    representationHelper(result, current->getLeftChild(), temp);
  } else {
    result += "\n" + path + "l>[NULL]";
  }
  //right side
  if (current->getRightChild()) {
    string temp = path + "r>";
    representationHelper(result, current->getRightChild(), temp);
  } else {
    result += "\n" + path + "r>[NULL]";
  }

}

string BSTree::getRepresentation()
{
  //implement function
  string result = "";
  string path = "";
  representationHelper(result, rootNode, path);
  return result;
}

BSTNode* getNodeHelper(string toFind, BSTNode* current) {
  if (!current || current->getKey() == toFind) {
    return current;
  } else if (current->getKey().compare(toFind) < 0) { //left
    return getNodeHelper(toFind, current->getLeftChild());
  } else { //right
    return getNodeHelper(toFind, current->getRightChild());
  }
}

BSTNode* BSTree::getNode(string key)
{
  //implement function
  return getNodeHelper(key, rootNode);
}


bool BSTree::addNode(string key)
{
  BSTNode* newNode = new BSTNode(key);
  addNode(newNode);
  return true;
}

bool addNodeHelper(BSTNode* toAdd, BSTNode* current) {
  if (toAdd->getKey().compare(current->getKey()) == 0) { //duplicate
    return false;
  } else if (toAdd->getKey().compare(current->getKey()) > 0) { //left hand
    if (!current->getLeftChild()) {
      current->setLeftChild(toAdd);
      return true;
    }
    return addNodeHelper(toAdd, current->getLeftChild());
  } else { //right hand
    if (!current->getRightChild()) {
      current->setRightChild(toAdd);
      return true;
    }
    return addNodeHelper(toAdd, current->getRightChild());
  }
}

bool BSTree::addNode(BSTNode* item)
{
  //implement function
  if (!rootNode) {
    rootNode = item;
    return true;
  }
  return addNodeHelper(item, rootNode);
}
