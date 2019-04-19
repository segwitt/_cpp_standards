/*

PROGRAM TO IMPLEMENT TREE HIERARCHY, name manager name

*/

#include <iostream>
#include <vector>
#include <map>
#include <fstream>

struct node
{
	node* parent;
	std::string key;
	std::vector< node* > nex;
	int sz;
	node() : parent(nullptr) , sz(0) , key(""){ }
	void addChild(node* child) {
		nex.push_back(child);
		sz++;
	}
	// parent and sz variables are not needed in this implementation
};


int chec(const std::string& parentName, const std::string& childName, std::map<std::string, node* >& m ) {
	// check if a childName is already some child of parentName
	int flag = 0;
	std::vector<node*>& v = m[parentName]->nex;
	for(const node* child : v) {
		if( child->key == childName ) flag = 1;
		flag |= chec(child->key, childName, m);
	}
	return flag;
}


node* addNode(const std::string& name) {
	node* newNode = new node();
	newNode->key = name;
	return newNode;
}



void load(const std::string& name , std::map<std::string, node* >&  m ) {
	if(m.find(name) == m.end()) {
		std::cout << "no such person exist\n";
		return ;
	}
	node* root = m[name];
	std::cout << name << " -- ";
	for(const node*  v : root->nex ) {
		load(v->key, m);
	}

}

void store(const std::string& name, const std::string& managerName, std::map<std::string, node* >& m) {

	if(m.find(managerName) == m.end() ) m[managerName] = addNode(managerName);
	if(m.find(name) == m.end() ) m[name] = addNode(name);


	if( chec( name, managerName , m) ) {
		// employee is already a parent node of manger so cannot allocate(cycle)
		std::cout << "cannot allocate\n";
		return ;
	}

	m[name]->parent = m[managerName];
	m[managerName]->addChild(m[name]);

}


std::vector<std::string> getTokens(const std::string& s) {

	std::string tmp = "";
	std::vector<std::string> v;
	for(char c : s) {
		if(c == ' ') {
			if(tmp != "") v.push_back(tmp);
			tmp = "";
			continue;
		}
		tmp += c;
	}
	if(tmp!="")v.push_back(tmp);
	return v;

}


int main() {


	std::map<std::string, node* > m; // to store the address of the manager names

	std::ifstream file("input.txt");
	
	if( file.is_open() ) {
		std::string line;
		while( getline(file, line) ) {
			std::vector<std::string> v = getTokens(line);
			if(!(int)v.size())continue;
			std::cout << "command-> ";
			for(auto x : v)std::cout << x << " ";
			std::cout << std::endl;
			
			if(v[0] == "load") {
				load(v[1], m);
				std::cout << std::endl;
			}
			else if (v[0] == "store"){
				std::string name = v[1];
				std::string managerName = v[2];

				store(name, managerName, m);

			}
			else {
				std::cout << "unrecognized command\n";
			}

		}
		file.close();

	}
	else std::cout << "Unable to open file\n";


}