# Online Store Management System (DSA)

An efficient e-commerce solution developed to address the challenges of managing product catalogs, stock levels, and order fulfillment. This project utilizes specialized Data Structures and Algorithms (DSA) to ensure high performance and scalability.

## 🛠️ DSA Implementations
To optimize system performance, the following data structures were used:

- **Binary Search Tree (BST):** Efficiently stores and searches the product catalog based on Product ID and Name. This allows for O(log n) search performance even with large inventories.
- **Queue (Linked List):** Manages incoming customer orders in a First-In-First-Out (FIFO) manner, ensuring fair and organized processing.
- **Singly Linked List:** Used to maintain a persistent record of checkout history for administrative review.

## 🚀 Key Features
### Admin Panel (PIN-Protected)
- **Inventory Control:** Add, update, or delete products directly from the BST.
- **Order Management:** Dispatch and process orders from the queue.
- **History Tracking:** View a comprehensive checkout history of all transactions.
- **Security:** Secure 4-digit PIN authentication (Default: 1234).

### User Panel
- **Smart Search:** Quickly find products by name within the inventory tree.
- **Ordering System:** Place orders with real-time stock validation and quantity checks.
- **Cart Summary:** View current orders with calculated total prices before checking out.

## 💻 Technical Stack
- **Language:** C++
- **Logic:** Data Structures and Algorithms (DSA)
- **Interface:** Console-based User Interface (CUI)

## 📝 Usage
1. Compile the source: `g++ "main.cpp" -o StoreSystem`
2. Run the executable.
3. Use the Admin panel (PIN: 1234) to populate the inventory.
4. Switch to the User panel to simulate the shopping and checkout experience.

## 👥 Contributors
- **Hassan Khalid** 
- **Maham Imran** 

---
*Developed for CS221(Data Structure and ALgorithm DSA) - Faculty of Computer Science and Engineering*
