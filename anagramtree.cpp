#include <iostream>
//#include <string>
#include <map>
//#include <cstddef>
#include <vector>
#include <set>
#include <fstream>
#include <memory>


class pointW{
public:
  //pointW(){};
  //pointW(char value, char weight);//,vector<std::set> wordSet,vector<pointW> branch);
  //~pointW();
  char value;
  char weight;
  std::set<std::string> wordSet;
  std::vector<std::shared_ptr<pointW>> branch;
};

pointW first = pointW();//("0","0");
bool isWordinTree(pointW Node, std::string str)//, std::string searchWord){
{
    if (str.empty())
    {
      //pointW.wordSet.insert(searchWord);
      if (Node.wordSet.empty())
      {
        return false;
      }
      else
      {
        std::cout << "Anagrams found: ";
        for(auto& c: Node.wordSet)
        {
          std::cout << c << std::endl;
        }
        return true;
      }
    }

    bool result = false;
    for(int i=0; i<Node.branch.size(); i++)
    {
      if(Node.branch[i]->value==str[0] && Node.branch[i]->weight ==str[1])
      {
        str = str.substr(2);
        result = isWordinTree(*Node.branch[i], str);//,searchWord);
        break;
      }
    }
    return result;
}


void buildTree(pointW& Node, std::string str, std::string searchWord)
{
    if (str.empty())
    {
      Node.wordSet.insert(searchWord);
        //std::cout << searchWord <<std::endl;
      return;
    }
    for(int i=0; i<Node.branch.size(); i++)
    {
      if(Node.branch[i]->value==str[0] && Node.branch[i]->weight ==str[1])
      {
        str = str.substr(2);
        buildTree(*Node.branch[i], str,searchWord);
        return;
      }
    }

    auto newpointW = std::make_shared<pointW>(); //(str[0],str[1]);
    newpointW->value = str[0];
    newpointW->weight = str[1];
    Node.branch.push_back(newpointW);//newSet, newpointW});
    str = str.substr(2);
    buildTree(*Node.branch.back(), str,searchWord);
}

int main()
{
  std::ifstream dictionary;
  dictionary.open("/Users/zangxiaoxue/step_google/STEP_GOOGLE/dictionary.txt", std::ios::in);
  if(!dictionary.is_open())
  {
    std::cout << "Unable to open dictionay." << std::endl;
    return -1;
  }
  std::string read_line;
  while(!dictionary.eof())
  {
    std::getline(dictionary, read_line);
      std::transform (read_line.begin (), read_line.end (), read_line.begin (), tolower);
      std::string read_word= read_line;
      std::sort(read_line.begin(), read_line.end());
      std::map<char, int> freq;
      for(auto& c: read_line)
      {
          if( freq.find(c) == freq.end())
              freq[c] = 1;
          else
              ++freq[c];
      }

      std::string input;
      for(auto& c: freq)
      {
          input += c.first;
          input += (c.second + '0');
      }
    //std::cout << read_line << std::endl;
      buildTree(first, input, read_word);
  }
  std::cout << "finish loading." << std::endl;
  std::string text;
  if (text.empty()){
  std::cout << "please input words." <<std::endl;
  std::getline(std::cin, text);
  }
    std::transform (text.begin (), text.end (), text.begin (), tolower);
  text.erase(remove_if(text.begin(), text.end(), isspace), text.end());
  std::sort(text.begin(), text.end());
  //std::cout << text << std::endl;
  std::map<char, int> freq;
  for(auto& c: text)
  {
    if( freq.find(c) == freq.end())
        freq[c] = 1;
    else
        ++freq[c];
  }
  std::string input;
  for(auto& c: freq)
  {
      input += c.first;
      input += (c.second + '0');
  }
    auto result = isWordinTree(first, input);
    if (!result){std::cout << "no result found!" << std::endl;}
}
