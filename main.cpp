#include<iostream>
#include<string>
using namespace std;

struct Product{
    int productId;
    string name;
    double price;
    int quantity;
    Product* left;
    Product* right;

    Product(int id, string n, double p, int q) : productId(id), name(n), price(p), quantity(q), left(NULL), right(NULL) {}
};

class ProductBST{
private:
    Product* root;

    Product* insertProduct(Product* root, int productId, string name, double price, int quantity){
        if(root==NULL)
            return new Product(productId, name, price, quantity);

        if(productId < root->productId)
            root->left=insertProduct(root->left, productId, name, price, quantity);
        else if(productId > root->productId)
            root->right=insertProduct(root->right, productId, name, price, quantity);

        return root;
    }

    Product* findProductByName(Product* root, string name){
        if(root == NULL)
            return NULL;
        if(root->name == name)
            return root;

        Product* left=findProductByName(root->left, name);
        if (left) return left;
        return findProductByName(root->right, name);
    }

    void displayProducts(Product* root){
        if(root == NULL)
            return;
        displayProducts(root->left);
        cout<<"ID: "<<root->productId<<", Name: "<<root->name<<", Price: $"<<root->price<<", Quantity: "<<root->quantity<<endl;
        displayProducts(root->right);
    }

    Product* findMin(Product* root){
        while(root && root->left != NULL)root=root->left;
        return root;
    }

    Product* deleteProduct(Product* root, int productId){
        if(root == NULL) return root;

        if(productId < root->productId)
            root->left = deleteProduct(root->left, productId);
        else if(productId > root->productId)
            root->right = deleteProduct(root->right, productId);
        else{
            if(root->left == NULL){
                Product* temp=root->right;
                delete root;
                return temp;
            }
            else if(root->right == NULL){
                Product* temp=root->left;
                delete root;
                return temp;
            }

            Product* temp=findMin(root->right);
            root->productId=temp->productId;
            root->name=temp->name;
            root->price=temp->price;
            root->quantity=temp->quantity;
            root->right=deleteProduct(root->right, temp->productId);
        }
        return root;
    }

public:
    ProductBST() : root(NULL){}
    void insertProduct(int productId, string name, double price, int quantity){
        root=insertProduct(root, productId, name, price, quantity);
    }
    Product* findProductByName(string name){
        return findProductByName(root, name);
    }
    void displayProducts(){
        displayProducts(root);
    }
    void deleteProduct(int productId){
        root=deleteProduct(root, productId);
    }
};

class Order{
public:
    int productId;
    string productName;
    int quantity;
    double price;
    double totalPrice;

    Order(int id, string name, int qty, double p) : productId(id), productName(name), quantity(qty), price(p) {
        totalPrice=price*quantity;
    }
};

class OrderQueue{
private:
    struct Node{
        Order* order;
        Node* next;
        Node(Order* ord) : order(ord), next(NULL){}
    };
    Node* front;
    Node* rear;

public:
    OrderQueue() : front(NULL), rear(NULL){}
    void enqueue(Order* order){
        Node* newNode=new Node(order);
        if(!rear){
            front=rear=newNode;
            return;
        }
        rear->next=newNode;
        rear=newNode;
    }
    Order* dequeue(){
        if (!front) return NULL;
        Node* temp=front;
        Order* order=front->order;
        front=front->next;
        delete temp;
        if (!front) rear = NULL;
        return order;
    }
    void displayOrders(){
        Node* temp = front;
        while(temp){
            cout<<"Product: "<<temp->order->productName<<", Quantity: "<<temp->order->quantity<<", Total Price: $"<<temp->order->totalPrice<<endl;
            temp=temp->next;
        }
    }
};

class CheckoutHistory{
private:
    struct Node{
        Order* order;
        Node* next;
        Node(Order* ord) : order(ord), next(NULL){}
    };
    Node* head;

public:
    CheckoutHistory() : head(NULL){}
    void addOrderToHistory(Order* order){
        Node* newNode=new Node(order);
        newNode->next=head;
        head=newNode;
    }
    void displayHistory(){
        Node* temp =head;
        if(!temp) cout << "No history available." << endl;
        while (temp){
            cout<<"Product: "<<temp->order->productName<<", Quantity: "<<temp->order->quantity<<", Total Price: $"<<temp->order->totalPrice<<endl;
            temp=temp->next;
        }
    }
};

class Admin{
private:
    int pin;
    CheckoutHistory checkoutHistory;

public:
    Admin() : pin(1234){} 
    bool validatePin(int enteredPin){ return enteredPin==pin; }
    void changePin(int newPin){ pin=newPin; }
    void viewCheckoutHistory(){ checkoutHistory.displayHistory(); }
    void addToCheckoutHistory(Order* order){ checkoutHistory.addOrderToHistory(order); }
};

class User{
public:
    string name;
    OrderQueue orderQueue;

    User(string username) : name(username){}
    void placeOrder(ProductBST& bst, string productName, int quantity){
        Product* product=bst.findProductByName(productName);
        if(product && product->quantity >= quantity){
            Order* order = new Order(product->productId, product->name, quantity, product->price);
            orderQueue.enqueue(order);
            product->quantity -= quantity;
            cout<<"Order placed successfully!"<<endl;
        } else {
            cout<<"Product not available or insufficient stock!"<<endl;
        }
    }
    void displayOrder(){ orderQueue.displayOrders(); }
    void checkout(Admin& admin){
        while(Order* order = orderQueue.dequeue()){
            admin.addToCheckoutHistory(order);
        }
    }
};

int main(){
    ProductBST bst;
    Admin admin;
    User* user = NULL;
    
    bst.insertProduct(234, "laptop", 2000, 5);
    bst.insertProduct(136, "mobile", 1500, 7);
    bst.insertProduct(512, "headphone", 500, 3);

    int choice;
    while (true){
        cout<<"\n-----Online Store-----";
        cout<<"\n1. Login as Admin\n2. Login as User\n3. Exit\nChoice: ";
        cin>>choice;

        if(choice == 1){
            int pin;
            cout<<"Enter Admin PIN: "; cin>>pin;
            if(admin.validatePin(pin)){
                int adminChoice;
                while(true){
                    cout<<"\nAdmin Panel:\n1. Add Product\n2. Delete Product\n3. View Checkout History\n4. Change Pin\n5. Exit Admin Panel\nChoice: ";
                    cin>>adminChoice;
                    if(adminChoice == 1){
                        int id, q; string n; double p;
                        cout<<"ID: "; cin>>id; cout<<"Name: "; cin>>n; cout<<"Price: "; cin>>p; cout<<"Qty: "; cin>>q;
                        bst.insertProduct(id, n, p, q);
                    } else if(adminChoice == 2){
                        int id; cout<<"ID to delete: "; cin>>id;
                        bst.deleteProduct(id);
                    } else if(adminChoice == 3){
                        admin.viewCheckoutHistory();
                    } else if(adminChoice == 4){
                        int np; cout<<"New PIN: "; cin>>np;
                        admin.changePin(np);
                    } else if(adminChoice == 5) break;
                }
            } else cout<<"Incorrect PIN."<<endl;
        } else if(choice == 2){
            string UserName;
            cout<<"Enter your name: "; cin>>UserName;
            user=new User(UserName);
            int userChoice;
            while(true){
                cout<<"\nWelcome "<<UserName<<"\n1. Display Products\n2. Search Product\n3. Place Order\n4. Display My Orders\n5. Checkout\n6. Exit\nChoice: ";
                cin>>userChoice;
                if(userChoice == 1) bst.displayProducts();
                else if(userChoice == 2){
                    string n; cout<<"Name: "; cin>>n;
                    Product* p = bst.findProductByName(n);
                    if(p) cout<<"Found: "<<p->name<<" Price: $"<<p->price<<endl;
                    else cout<<"Not found."<<endl;
                } else if(userChoice == 3){
                    string n; int q; cout<<"Name: "; cin>>n; cout<<"Qty: "; cin>>q;
                    user->placeOrder(bst, n, q);
                } else if(userChoice == 4) user->displayOrder();
                else if(userChoice == 5){ user->checkout(admin); cout<<"Checked out!"; break; }
                else if(userChoice == 6) break;
            }
        } else if(choice == 3) break;
    }
    delete user;
    return 0;
}