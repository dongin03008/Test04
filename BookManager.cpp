#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

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
            cout << "현재 대여가능 수량이 " << stock[title] << "남았습니다. 대여하시겠습니까?" << endl;
            cout << "1.예" << endl << "2.아니요"<<endl;
            cin >> i;
            if (i == 1) {
                cout << "대여가 완료되었습니다." << endl;
                stock[title]--;
                return;
            }
            else if (i == 2) {
                cout << "대여하지 않습니다. " << endl;
                return;
            }
        }
        else {
            cout << "남은 수량이 없어 대여가 불가능합니다." << endl;
        }
    }
    void returnBook(string title) {
        if (stock[title] < 3) {
            cout << "반납 되었습니다" << endl;
            stock[title]++;
        }
        else {
            cout << "이미 모든책이 도서관에 있습니다" << endl;
        }
    }
    void displayStock() {
        for (auto const& pair : stock) {
            cout << "책 : " << pair.first << " 남은수량 : " << pair.second << endl;
        }
    }
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장
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
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        borrow.initializeStock(Book(title, author));
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    void searchByTitle()
    {
        string title;
        cout << "책 제목을 입력해 주세요 : ";
        getline(cin, title);
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == title) {
                cout << "작가는 " << books[i].author << "입니다" << endl;
                break;
            }
        }
    }
    void searchByAuthor() 
    {
        string title;
        cout << "작가 이름을 입력해 주세요 : ";
        getline(cin, title);
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == title) {
                cout << "책 제목은" << books[i].title << "입니다" << endl;
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
        cout << "1.대여" << endl << "2.반납" <<endl<<"3.대여수량 확인" << endl;
        cin >> num;
        if (num == 1) {
            cout << "1. 책이름으로 대여" << endl << "2. 작가이름으로 대여"<<endl;
            cin >> num;
            if (num == 1) {
                cin.ignore();
                cout << "책 이름을 입력해 주세요 : "<<endl;
                getline(cin, st);
                getBookbyTitle(st);
            }
            else if (num == 2) {
                cin.ignore();
                cout << "작가 이름을 입력해 주세요 : "<<endl;
                getline(cin, st);
                getBookbyAuthor(st);
            }
        }
        else if(num == 2){
            cin.ignore();
            cout << "반납하실 책 제목을 입력해 주세요" << endl;
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

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 대여" << endl; // 프로그램 종료
        cout << "4. 종료 : " << endl;
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 4) {
            // 4번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else if (choice == 3) {
            //3번 선택: 대여
            // 대여 메세지를 띄웁니다
            manager.borrowAndReturn();
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}