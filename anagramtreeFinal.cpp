#include <iostream>
//#include <string>
#include <map>
//#include <cstddef>
#include <vector>
#include <set>
#include <fstream>
#include <memory>
#include <bitset>


class pointW{
public:
  char value;
  char weight;
  std::set<std::string> wordSet;
  std::vector<std::shared_ptr<pointW>> branch;
};

pointW first = pointW();//("0","0");
std::vector<std::string> answers;
int longestAnagramLength;
void isWordinTree(pointW Node, std::string str)
{
    if (str.empty())
    {

      if (Node.wordSet.empty())
      {
        return;// false;
      }
      else
      {

        for(auto& c: Node.wordSet)
        {
          answers.push_back(c);
            if(c.size()>longestAnagramLength){longestAnagramLength = c.size();}
            //std::cout << c << std::endl;
        }
        return; //true;
      }
    }


    for(int i=0; i<Node.branch.size(); i++)
    {
      if(Node.branch[i]->value==str[0] && (Node.branch[i]->weight <=str[1]) &&(Node.branch[i]->weight >= '0'))
      {
          std::string strNew = str.substr(2);
        isWordinTree(*Node.branch[i], strNew);
      }
    }
    str = str.substr(2);
    isWordinTree(Node, str);
    return;// result;
}


void buildTree(pointW& Node, std::string str, std::string searchWord)
{
    if (str.empty())
    {
      Node.wordSet.insert(searchWord);
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

    auto newpointW = std::make_shared<pointW>();
    newpointW->value = str[0];
    newpointW->weight = str[1];
    Node.branch.push_back(newpointW);
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


  std::map<char, int> freq;
  for(auto& c: text)
  {
    if( freq.find(c) == freq.end())
        freq[c] = 1;
    else
        ++freq[c];
  }
    longestAnagramLength = 0;
    std::string input;
  for(auto& c: freq)
  {
      input += c.first;
      input += (c.second + '0');
  }

    isWordinTree(first, input);
    for (auto& item: answers)
    {
        if(item.size()==longestAnagramLength)
        {
            std::cout << "the Anagram is " << item << std::endl;
        }
    }

}
