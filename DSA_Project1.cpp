/*
Project Group Members:
1.Numan Maroof (F202340126)
2.Usman Tariq (F2023408116)
*/
/*
Project: Multi User Chat application with file handling
Make a subfolder named "Privatechats" and "Groupchats" in the same folder before running.(if not created already)
*/
#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include <vector>
using namespace std;
const char* subfolder = "./Privatechats";
const char* subfolder1 = "./Groupchats";
char originalpath[MAX_PATH];
// node class for queue of messages
class nodem {
public:
	string msg;
	nodem* next;
	nodem(string m):msg(m),next(NULL) {}
};
// Queue using Linked List to store messages
class queuemsgs {
	nodem* head;
public:
	queuemsgs():head(NULL) {}
	// Insert messages to the queue
	void insert(string m) {
		nodem* newnode = new nodem(m);
		if(head == NULL) {
			head = newnode;
		}
		else {
			nodem* temp = head;
			while(temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newnode;
		}
	}
	// Deletes the whole list
	void dele() {
	    nodem* temp = head;
        nodem* temp1 = NULL;
        while (temp != NULL) {
            temp1 = temp->next;  
            delete temp;            
            temp = temp1;        
        }
        head = NULL;
	}
	// Displays whole list
	void display() {
		if(!head) {
			cout<<"No messages!"<<endl;
			return;
		}
		nodem* temp = head;
		while(temp != NULL) {
			cout<<temp->msg<<endl;
			temp = temp->next;
		}
	}
	// Store messages into the respected files
	void storem(string name,char a) {
		if(a == 'p')
			SetCurrentDirectory(subfolder);
		else if (a == 'g'){
			SetCurrentDirectory(subfolder1);
		}
		ofstream w(name);   //open the file 
        if (!w.is_open()) {
            cerr << "Error: Could not open file " << name << " for writing." << endl;
			cout<<"Press Enter to continue ....";
			cin.ignore();
            cin.get();
            return;
        }
		nodem* temp= head;
		while(temp != NULL) {
			w<<temp->msg<<endl;
			temp = temp->next;
		}
		w.close();
		SetCurrentDirectory(originalpath);
	}
};
// Node class for Contact list
class node {
public:
	queuemsgs m;   //Every contact will have a queue of messages
	string fname, lname;
	node* next ;
	node(string n,string l):fname(n),lname(l),next(NULL){}
};
// Linked List to store contacts as nodes
class Privatechats {
	node* head;
public:
	Privatechats():head(NULL) {}  
	// Add the Privatechats to the list      
	void add(string f, string l) {
			node* newnode = new node(f,l);
			if(head == NULL) {
				head = newnode;
			}
			else {
				node* temp = head;
				while(temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = newnode;
			}
	}
	// Deletes the conteact from the list
	void del(string f , string l) {
	    if(search(f,l)){
    		if(f == head->fname) {
    			node* temp = head;
    			head = temp->next;
    			temp->m.dele();
    			delete temp;
    		}
    		else{
    			node* temp = head;
    			node* temp1 = head->next;
    			while(temp1->next != NULL && temp1->fname!=f && temp1->lname!=l) {
    				temp = temp1;
    				temp1 = temp1->next;
    			}
    			node* deln = temp->next;
    			temp->next = deln->next;
    			deln->m.dele();
    			delete deln;
    		}
            cout<<"Contact deleted Successfully!"<<endl;
			cout<<"Press Enter to continue ....";
            cin.ignore();
            cin.get();
	    }else{
            cout<<"No such contact!"<<endl;
			cout<<"Press Enter to continue ....";
            cin.ignore();
            cin.get();
        }
	}        
	// Displays the Full list of Privatechats
	void display() {
		if(head == NULL) {
			cout<<"No Contacts!"<<endl;
			return ;
		}
		node* temp = head;
		while(temp != NULL) {
			cout<<temp->fname<<" "<<temp->lname<<endl;
			temp = temp->next;
		}
	}
	// Displays the message store in the queue of repective contact  
	void enter(string f, string l) {
		node* temp= head;
        while(temp->next != NULL && temp->fname != f && temp->lname != l){
            temp = temp->next;
        }
        temp->m.display();
	}
	// Insert the message into the queue of respective contact
	void enter(string f,string l,string n,string msg = "") {
            node* temp= head;
            while(temp->next != NULL && temp->fname != f && temp->lname != l) {
                temp = temp->next;
            }
            if(msg == "")                
                return;
            else                    
                temp->m.insert(n+msg);
	}        
	// Store messages into the respected files of respective contact
	void store(string f, string l) {
            node* temp= head;
            while(temp != NULL && temp->fname != f && temp->lname != l) {
                temp = temp->next;
            }
            if (temp != NULL) {
				temp->m.storem(f+l+".txt",'p');
			} else {
				cerr << "Error: Node with fname '" << f+l << "' not found." << endl;
				cout<<"Press Enter to continue ....";
				cin.ignore();
				cin.get();
			}
	}
	// Search the contact
	bool search(string f,string l){
	    node* temp = head;
	    while(temp != NULL){
	        if(temp->fname == f &&temp->lname == l)
	            return true;
	        temp = temp->next;
	    }
	    return false;
	}	
};
class nodec{
	public:
		queuemsgs m;
		vector<string> members;
		string name;
		nodec* next;
		nodec(string n){
			next = NULL;
			name = n;
		}
};
class groupchat{
	public:
	nodec* head;
		groupchat():head(NULL){}
		// Creates a new group
		void create(string name){
			nodec* newnode = new nodec(name);
			if(head == NULL) {
				head = newnode;
			}
			else {
				nodec* temp = head;
				while(temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = newnode;
			}
		}
		// deletes a group
		void exit(string cn){
			if(search(cn)){
				if(cn == head->name) {
					nodec* temp = head;
					head = temp->next;
					temp->m.dele();
					delete temp;
				}
				else{
					nodec* temp = head;
					nodec* temp1 = head->next;
					while(temp1->next != NULL && temp1->name != cn) {
						temp = temp1;
						temp1 = temp1->next;
					}
					nodec* deln = temp->next;
					temp->next = deln->next;
					deln->m.dele();
					delete deln;
				}
				cout<<"Chat deleted Successfully!"<<endl;
				cout<<"Press Enter to continue ....";
				cin.ignore();
				cin.get();
			}else{
				cout<<"No such Chat!"<<endl;
				cout<<"Press Enter to continue ....";
				cin.ignore();
				cin.get();
			}
		}
		// Displays the message store in the queue of repective group  
		void enter(string n) {
			nodec* temp= head;
			while(temp->next != NULL && temp->name != n){
				temp = temp->next;
			}
			temp->m.display();
		}
		// Insert the message into the queue of respective group
		void enter(string cn,string n,string msg = "") {
				nodec* temp= head;
				while(temp->next != NULL && temp->name != cn) {
					temp = temp->next;
				}
				if(msg == "")                
					return;
				else
					temp->m.insert(n+msg);
		} 
		// Add people to group
		void add(string cn,string fn){
				nodec* temp= head;
				while(temp->next != NULL && temp->name != cn) {
					temp = temp->next;
				}
				for(int i=0; i<temp->members.size(); i++){
					if(fn == temp->members[i]){
						cout<<"User already added!"<<endl;
						cout<<"Press Enter to continue ....";
						cin.ignore();
						cin.get();
						return;
					}
				}
				temp->members.push_back(fn);
		}
		// Remove people from group
		void remov(string cn,string fn,string ln){
			nodec* temp= head;
			while(temp->next != NULL && temp->name != cn) {
				temp = temp->next;
			}
			// removing index from vector
			for (auto it = temp->members.begin(); it != temp->members.end(); ) {
				if (*it == fn) {
					it = temp->members.erase(it); // Erase the element and get the next valid iterator
				} else {
					++it; 
				}
			}
			SetCurrentDirectory(originalpath);
			ifstream f;
			ofstream f1("temp.txt");
			f.open(cn);
			string line;
			while(getline(f,line)){
				if(line != fn){
					f1<<line<<endl;
				}
			}
			f.close();
			f1.close();
			remove(cn.c_str());
			rename("temp.txt",cn.c_str());
		}
		// Displays the Names of groups
		void display(){
			if(head == NULL) {
				cout<<"No Contacts!"<<endl;
				return ;
			}
			nodec* temp = head;
			while(temp != NULL) {
				cout<<temp->name<<endl;
				temp = temp->next;
			}
		}
		// Search for group name
		bool search(string cn){
			nodec* temp = head;
			while(temp != NULL){
				if(temp->name == cn)
					return true;
				temp = temp->next;
			}
			return false;
		}
		// take messages from the members of the group
		void traverse(string name){
			nodec* temp= head;
			while(temp->next != NULL && temp->name != name) {
				temp = temp->next;
			}
			string message;
			for(int i=0; i<temp->members.size();i++){
				do {
					cout<<temp->members[i]<<": ";
					getline(cin,message);
					enter(name,temp->members[i]+": ",message);
				}while(message!="");
			}
		}
		// Store the mesasges into files
		void store(string name) {
            nodec* temp= head;
            while(temp != NULL && temp->name != name) {
                temp = temp->next;
            }
			// SetCurrentDirectory(subfolder1);
			SetCurrentDirectory(originalpath);
			ofstream w(name);
			for(int i=0; i<temp->members.size(); i++){
				w<<temp->members[i]<<endl;
			}
			w.close();
            if (temp != NULL) {
				cout<<"check"<<endl;
				temp->m.storem(name+".txt",'g');
			} else {
				cerr<<"Error: Node with fname '"<<name<<"' not found."<<endl;
				cout<<"Press Enter to continue ....";
				cin.ignore();
				cin.get();
			}
		}
};
// This will load all the data from privatechat files to list and queue
void start(Privatechats& c) {  
	SetCurrentDirectory(subfolder);
    HANDLE find;
    WIN32_FIND_DATA data;
	
	string folder = originalpath;
	string f = "\\Privatechats\\*";
	folder = folder+f;
	const char* ch = folder.c_str();
	find = FindFirstFile(ch, &data);
    if(find == INVALID_HANDLE_VALUE){
        cerr<< "Error opening directory!"<<endl;
        return;
    }
	// Traversing through file names inside contact folder
    do{
        string fileName = data.cFileName;
        string  f1 = "", f2 ="";
        f1 += fileName.at(0);

        if (fileName != "." && fileName != "..") {
            int i = 1;
            while (i < fileName.size()) {
                char c = fileName.at(i);
                if (isupper(c) ){
                    while (i < fileName.size()) {
                        c = fileName.at(i);
                        if(c == '.')
                            break;  
                        f2 += c;
                        i++;
                    }
                    break;
                }else{
                    f1 += c;
                }  
                i++;
            }
            if (!f1.empty()) {
                c.add(f1, f2);  
            }
            ifstream file;  // Open file for reading
			file.open(fileName);
            string line;
            while (getline(file,line)) {  // Read line by line
                c.enter(f1,f2,"",line);
            }
            file.close();
        }
    } while (FindNextFile(find, &data) != 0);
    FindClose(find);
	SetCurrentDirectory(originalpath);
}
// This will load all the data from groupchat files to list and queue
void start(groupchat& c) {
    HANDLE find;
    WIN32_FIND_DATA data;
	
    string folder = originalpath;
	string f = "\\Groupchats\\*";
	folder = folder+f;
	const char* ch = folder.c_str();
	find = FindFirstFile(ch, &data);
    if(find == INVALID_HANDLE_VALUE){
        cerr<< "Error opening directory!"<<endl;
        return;
    }
	// Traversing through file names inside contact folder
    do{
		SetCurrentDirectory(subfolder1);
        string fileName = data.cFileName;
        string  f1 = "";

        if (fileName != "." && fileName != "..") {
            int i = 0;
            while (i < fileName.size()) {
                char c = fileName.at(i);
                if(c == '.')
                    break;  
                i++;
                f1 += c;
                }
            if (!f1.empty()) {
                c.create(f1);  
            }
            ifstream file;
			file.open(fileName);  // Open file for reading
            string line;
            while (getline(file, line)) {  // Read line by line
				c.enter(f1,"",line);
            }
            file.close();
			nodec* temp = c.head;
			while(temp->name != f1) {
				temp = temp->next;
			}
			SetCurrentDirectory(originalpath);
			ifstream file1;
			file1.open(f1);
			while(getline(file1,line)){
				c.add(f1,line);
			}
		}
    }while(FindNextFile(find, &data) != 0);
    FindClose(find);
	SetCurrentDirectory(originalpath);
}
int main() {
    // Save the current directory
    GetCurrentDirectory(MAX_PATH, originalpath);

	string fn,ln,name;
	Privatechats c;
	groupchat gc;
	start(c);
	start(gc);
	cout<<"!!Welcome to Chat App!!"<<endl;
	cout<<"Press Enter to continue ....";
	cin.ignore();
	cin.get();
here:
	system("cls");
	cout<<"1.View Contacts and groups"<<endl        
	<<"2.Add Contact"<<endl        
	<<"3.Remove Contact"<<endl        
	<<"4.Enter chat"<<endl
	<<"5.Exit Application"<<endl;
	int ch;
	cin>>ch;
	system("cls");
	// Views all contacts and groups
	if(ch==1) {
		cout<<"Private Chats: "<<endl;
		c.display();
		cout<<endl<<"Group Chats: "<<endl;
		gc.display();
		cout<<"Press Enter to continue ....";
		cin.ignore();
		cin.get();
		goto here;
	} // Add contacts
	else if(ch == 2) {
		cout<<"Enter First name: ";
		cin>>fn;
		fn[0] = toupper(fn[0]);
		cout<<"Enter Last name: ";
		cin>>ln;
		ln[0] = toupper(ln[0]);
		// creating files 
		if(!c.search(fn,ln)){
			c.add(fn,ln);
			SetCurrentDirectory(subfolder);
			string name = fn+ln+".txt";
			ofstream file(name);
			cout<<"Contact added successfully!"<<endl;
			cout<<"Press Enter to continue ....";
			cin.ignore();
			cin.get();
			SetCurrentDirectory(originalpath);
		}else{
			cout<<"Contact already exist!"<<endl;
			cout<<"Press Enter to continue ....";
			cin.ignore();
			cin.get();
		}
		goto here;
	} // Deleting contacts
	else if(ch == 3) {
		cout<<"Enter the first and last name of contact: ";
		cin>>fn>>ln;
		c.del(fn,ln);
		// deleting the file
		SetCurrentDirectory(subfolder);
		fn = fn+ln+".txt";
		const char* r = fn.c_str();
		remove(r); //Removes files of the deleted contact
		SetCurrentDirectory(originalpath);
		goto here;
	}
	else if(ch== 4){
		here1:
		system("cls");
		cout<<"1.Private chat"<<endl
		<<"2.Group chat"<<endl
		<<"3.Go back"<<endl;
		cin>>ch;
		// Goes to Private chats
		if(ch == 1){
			SetCurrentDirectory(subfolder);
			cout<<"Which chat do u want to enter: ";
			cin>>fn>>ln;
			system("cls");
			if(c.search(fn,ln)){
				cout<<"Press 'q' or 'Q' to exit chat"<<endl;
				c.enter(fn,ln);
				string message;
				bool b = true;
				// These loops will take messages and process them
				// Press 'q' or 'Q' to exit whole chat
				do {
					do{
						cout<<fn<<": ";
						getline(cin,message);
						if(message == "q" || message== "Q") {
							b=false;
							break;
						}
						c.enter(fn,ln,fn+": ",message);
					}while(message!="");
					do {
						cout<<"You: ";
						getline(cin,message);
						if(message == "q" || message== "Q") {
							b=false;
							break;
						}
						c.enter(fn,ln,"You: ",message);
					}while(message!="");
				}while(b);
				c.store(fn,ln);// store messages to files
			}else{
				cout<<"No such Contact!"<<endl;
				cout<<"Press Enter to continue ....";
				cin.ignore();
				cin.get();
			}
			SetCurrentDirectory(originalpath);
			goto here1;
		} //goes to Group chat options
		else if (ch == 2){
			here2:
			system("cls");
			cout<<"1.Create Group"<<endl
			<<"2.Leave/Delete Group"<<endl
			<<"3.Enter Group"<<endl
			<<"4.Go back"<<endl;
			cin>>ch;
			//Create Group
			if(ch == 1){
				cout<<"Enter the name: ";
				cin.ignore();
				getline(cin,name);
				if(!gc.search(name)){
					gc.create(name);
					SetCurrentDirectory(subfolder1);
					name = name+".txt";
					ofstream file(name);
					cout<<"Group created successfully!"<<endl;
					SetCurrentDirectory(originalpath);
					cout<<"Press Enter to continue ....";
					cin.get();
				}else{
					cout<<"Group already exist!"<<endl;
					cout<<"Press Enter to continue ....";
					cin.get();
				}
				goto here2;
			}//delete or leave group
			else if(ch == 2){
				cout<<"Enter the name: ";
				cin>>name;
				gc.exit(name);
				const char* r = name.c_str();
				remove(r);
				SetCurrentDirectory(subfolder1);
				name = name+".txt";
				r = name.c_str();
				remove(r); //Removes files of the deleted contact
				SetCurrentDirectory(originalpath);

				goto here2;
			} //Enters the group chat
			else if(ch == 3){
				cout<<"Which Chat u want to enter: ";
				cin>>name;
				if(gc.search(name)){
					here3:
					system("cls");
					cout<<"1.Add user"<<endl
					<<"2.Remove user"<<endl
					<<"3.Start chatting"<<endl
					<<"4.Go back"<<endl;
					cin>>ch;
					// Add someone
					if(ch == 1){
						cout<<"Enter the first and last name: ";
						cin>>fn>>ln;
						if(c.search(fn,ln)){
							gc.add(name,fn);
						}else{
							cout<<"Add this contact first!"<<endl;
							cout<<"Press Enter to continue ....";
							cin.ignore();
							cin.get();
						}
						goto here3;
					}// Remove someone
					else if(ch == 2){
						cout<<"Enter the first and last name: ";
						cin>>fn>>ln;
						if(c.search(fn,ln)){
							gc.remov(name,fn,ln);
						}else{
							cout<<"No such contact!"<<endl;
							cout<<"Press Enter to continue ....";
							cin.ignore();
							cin.get();
						}
						goto here3;
					} // Start chating
					else if(ch == 3){
						cout<<"Press 'q' or 'Q' to exit chat"<<endl;
						gc.enter(name);
						string message;
						bool b = true;
						// These loops will take messages and process them
						while(b){
							gc.traverse(name);
							do {
								cout<<"You: ";
								getline(cin,message);
								if(message == "q" || message== "Q") {
									b=false;
									break;
								}
								gc.enter(name,"You: ",message);
							}while(message!="");
						}
						gc.store(name);
						goto here3;
					} //goes to 3rd menu
					else if(ch == 4){
						goto here2;
					}else{
						cout<<"Wrong option!"<<endl;
						cout<<"Press Enter to continue ....";
						cin.ignore();
						cin.get();
					}
				}else{
					cout<<"No such Contact!"<<endl;
					cout<<"Press Enter to continue ....";
					cin.ignore();
					cin.get();
				}
				goto here2;
			}//goes to second menu
			else if(ch == 4){
				goto here1;
			}//Wrong option for group chat
			else{
				cout<<"Wrong option!"<<endl;
				cout<<"Press Enter to continue ....";
				cin.ignore();
				cin.get();
				goto here2;
			}
		} // Goes to first menu 
		else if(ch == 3){
			goto here;
		} //Wrong option for PRivate or group
		else{
			cout<<"Wrong option!"<<endl;
			cout<<"Press Enter to continue ....";
			cin.ignore();
			cin.get();
			goto here1;
		}
	}//Exiting app
	else if(ch == 5) {
		cout<<"EXITING!!!";
	}
	else {
		cout<<"No such option!"<<endl;
		cout<<"Press Enter to continue ....";
		cin.ignore();
		cin.get();
		goto here;
	}
}