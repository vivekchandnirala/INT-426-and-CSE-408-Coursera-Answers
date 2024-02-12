#include <bits/stdc++.h>
#define pb push_back
#define MAX_CHAR 256
#define FOR(i,a,b) for(int i=a;i<b;i++)

using namespace std;

struct Node{
  vector<Node*> nextNodes;
  vector<pair<int,int> > edges;
};

int getCommonStrLen(const string &text, int startPos1, int startPos2, int string1Len){
  int sameCharNum = 0;
  while(text[startPos1+sameCharNum] == text[startPos2 + sameCharNum]){
    sameCharNum++;
    if((sameCharNum==string1Len)||(startPos2+sameCharNum)==text.size()){
      break;
    }
  }
  return sameCharNum;
}

void updateTree(Node *root, const string &text, int subStringIndex){
  if(subStringIndex >= text.size()){
    return ;
  }
  for(int i=0;i<root->nextNodes.size();i++){
    int startingPos = root->edges[i].first;
    int commonStrLen = getCommonStrLen(text, startingPos, subStringIndex, root->edges[i].second);
    if((commonStrLen>0)&&(commonStrLen<root->edges[i].second)){
      Node *oldNode = root->nextNodes[i];
      Node *newNode = new Node;
      pair<int,int> partOldEdge (startingPos+commonStrLen, root->edges[i].second-commonStrLen);
      pair<int,int> newEdge (subStringIndex+commonStrLen, text.size()-subStringIndex-commonStrLen);
      Node *middle = new Node;
      middle->nextNodes.pb(oldNode);
      middle->nextNodes.pb(newNode);
      middle->edges.pb(partOldEdge);
      middle->edges.pb(newEdge);
      root->nextNodes[i] = middle;
      root->edges[i].second = commonStrLen;
      return;
    }else if(commonStrLen==root->edges[i].second){
      Node *nextNode = root->nextNodes[i];
      updateTree(nextNode, text, subStringIndex + commonStrLen);
      return;
    }else if((commonStrLen==0)&&(i==root->nextNodes.size()-1)){
      Node *newNode = new Node;
      root->nextNodes.pb(newNode);
      pair<int,int> newEdge(subStringIndex,text.size()-subStringIndex);
      root->edges.pb(newEdge);
      return;
    } 
  }
  Node *nextNode = new Node;
  root->nextNodes.pb(nextNode);
  pair<int,int> stringIndex (subStringIndex, text.size()-subStringIndex);
  root->edges.pb(stringIndex);
  return;
}

void getSubStrings(Node *root, const string &text, vector<string>& result){
  for(int i=0;i<root->nextNodes.size();i++){
    result.pb(text.substr(root->edges[i].first,root->edges[i].second));
    Node *nextNode = root->nextNodes[i];
    getSubStrings(nextNode,text,result);
  }
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
  Node *root = new Node;
  for(int i=0;i<text.size();i++){
    updateTree(root,text,i);
  }
  getSubStrings(root,text,result);
  
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
