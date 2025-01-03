#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std ���

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BorrowManager {
private:
    unordered_map<string, int> stock;

public:
    void initializeStock(Book books) {
        stock.insert({ books.title,3});
    }
    void borrowBook(string title) {
        int i=0;
        if (stock[title] > 0) {
            cout << "���� �뿩���� ������ " << stock[title] << "���ҽ��ϴ�. �뿩�Ͻðڽ��ϱ�?" << endl;
            cout << "1.��" << endl << "2.�ƴϿ�"<<endl;
            cin >> i;
            if (i == 1) {
                cout << "�뿩�� �Ϸ�Ǿ����ϴ�." << endl;
                stock[title]--;
                return;
            }
            else if (i == 2) {
                cout << "�뿩���� �ʽ��ϴ�. " << endl;
                return;
            }
        }
        else {
            cout << "���� ������ ���� �뿩�� �Ұ����մϴ�." << endl;
        }
    }
    void returnBook(string title) {
        if (stock[title] < 3) {
            cout << "�ݳ� �Ǿ����ϴ�" << endl;
            stock[title]++;
        }
        else {
            cout << "�̹� ���å�� �������� �ֽ��ϴ�" << endl;
        }
    }
    void displayStock() {
        for (auto const& pair : stock) {
            cout << "å : " << pair.first << " �������� : " << pair.second << endl;
        }
    }
};

class BookManager {
private:
    vector<Book> books; // å ��� ����
    BorrowManager borrow;

    Book* findBookByTitle(string title) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == title) {
                return &books[i];
            }
        } 
    }
    Book* findBookByAuthor(string title) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].author == title) {
                return &books[i];
            }
        }
    }

public:
    // å �߰� �޼���
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back ���
        borrow.initializeStock(Book(title, author));
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
    }

    // ��� å ��� �޼���
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // �Ϲ����� for�� ���
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    void searchByTitle()
    {
        string title;
        cout << "å ������ �Է��� �ּ��� : ";
        getline(cin, title);
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == title) {
                cout << "�۰��� " << books[i].author << "�Դϴ�" << endl;
                break;
            }
        }
    }
    void searchByAuthor() 
    {
        string title;
        cout << "�۰� �̸��� �Է��� �ּ��� : ";
        getline(cin, title);
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == title) {
                cout << "å ������" << books[i].title << "�Դϴ�" << endl;
                break;
            }
        }
    }
    void getBookbyTitle(string title)
    {
        Book *book = findBookByTitle(title);
        string name = book->title;
        borrow.borrowBook(name);
    }
    void getBookbyAuthor(string author)
    {
        Book* book = findBookByAuthor(author);
        string name = book->title;
        borrow.borrowBook(name);
    }
    void borrowAndReturn() {
        int num;
        string st;
        cout << "1.�뿩" << endl << "2.�ݳ�" <<endl<<"3.�뿩���� Ȯ��" << endl;
        cin >> num;
        if (num == 1) {
            cout << "1. å�̸����� �뿩" << endl << "2. �۰��̸����� �뿩"<<endl;
            cin >> num;
            if (num == 1) {
                cin.ignore();
                cout << "å �̸��� �Է��� �ּ��� : "<<endl;
                getline(cin, st);
                getBookbyTitle(st);
            }
            else if (num == 2) {
                cin.ignore();
                cout << "�۰� �̸��� �Է��� �ּ��� : "<<endl;
                getline(cin, st);
                getBookbyAuthor(st);
            }
        }
        else if(num == 2){
            cin.ignore();
            cout << "�ݳ��Ͻ� å ������ �Է��� �ּ���" << endl;
            cin >> st;
            borrow.returnBook(st);
        }
        else if (num == 3) {
            borrow.displayStock();
        }
    }

};

int main() {
    BookManager manager;

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. �뿩" << endl; // ���α׷� ����
        cout << "4. ���� : " << endl;
        cout << "����: ";

        int choice; // ������� �޴� ������ ����
        cin >> choice;

        if (choice == 1) {
            // 1�� ����: å �߰�
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager.addBook(title, author); // �Է¹��� å ������ �߰�
        }
        else if (choice == 2) {
            // 2�� ����: ��� å ���
            // ���� BookManager�� ����� å ����� ����մϴ�.
            manager.displayAllBooks();
        }
        else if (choice == 4) {
            // 4�� ����: ����
            // ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
            cout << "���α׷��� �����մϴ�." << endl;
            break; // while ���� ����
        }
        else if (choice == 3) {
            //3�� ����: �뿩
            // �뿩 �޼����� ���ϴ�
            manager.borrowAndReturn();
        }
        else {
            // �߸��� �Է� ó��
            // �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0; // ���α׷� ���� ����
}