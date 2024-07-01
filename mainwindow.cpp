#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>
QString del(int number)
{
    QString s1="простое";
    QString s2="непростое";

    if (number <= 1) {
        return s2;
    }
    if (number <= 3) {
        return s1;
    }
    if (number % 2 == 0 || number % 3 == 0) {
        return s2;
    }

    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return s2;
        }
    }
    return s1;
}
template<typename T>
class MyStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode;
    int size;

public:
    MyStack() : topNode(nullptr), size(0) {}

    ~MyStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        size++;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        size--;
    }

    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return topNode->data;
    }

    bool isEmpty() const {
        return (size == 0);
    }
    T Size()
    {
        return size;
    }
};

void readInputFromFile(const QString& filename, MyStack<int>& numbersStack) {
    QFile inputFile(filename);

    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        int number;
        while (!in.atEnd()) {
            in >> number;
            numbersStack.push(number);
        }
        inputFile.close();
    }
    else {
        std::cout << "File " << filename.toStdString() << " is not open for read." << std::endl;
        exit(0);
    }
}

void writeOutputToFile(const QString& filename, const MyStack<int>& numbersStack) {
    QFile outputFile(filename);

    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&outputFile);
        MyStack<int> tempStack = numbersStack;
        while (!tempStack.isEmpty()) {
            out << tempStack.top() << " ";
            tempStack.pop();
        }
        outputFile.close();
    }
    else {
        std::cout << "File " << filename.toStdString() << " is not open for write." << std::endl;
    }
}

MyStack<int> removeTwoDigitNumbers(const MyStack<int>& numbersStack) {
    MyStack<int> resultStack;
    MyStack<int> tempStack = numbersStack;

    while (!tempStack.isEmpty()) {
        int number = tempStack.top();
        tempStack.pop();

        if (number < 10 or number > 99) {
            resultStack.push(number);
        }
    }

    return resultStack;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString inputFilename = "Input.txt";
    // Чтение чисел из файла в стек
    MyStack<int> resultStack;
    MyStack<int> resultS;
    readInputFromFile(inputFilename, resultStack);
    int n=0;
    while (!resultStack.isEmpty()) {
        int number = resultStack.top();
        resultStack.pop();

        if (number < 10 or number > 99) {
            resultS.push(number);
            n++;
        }
    }
    // Удаление двузначных чисел из стека и получение нового стека
    //MyStack<int> resultStack = removeTwoDigitNumbers(numbersStack);


    // Установка размеров таблицы
    ui->tableWidget->setRowCount(n-1); // Устанавливаем количество строк
    ui->tableWidget->setColumnCount(2); // Устанавливаем количество столбцов

    // Заполнение таблицы данными
    QStringList header;
    header << "Элемент" << "Делители";
    ui->tableWidget->setHorizontalHeaderLabels(header);

    int row=0;

    //for (int row = 0; row < resultS.Size(); ++row) {
    while(!resultS.isEmpty())
    {
        int elem =resultS.top();
        resultS.pop();

        QString str = QString::number(elem);
        QString prostota=del(elem);
        QTableWidgetItem* elemItem = new QTableWidgetItem(str);
        QTableWidgetItem* delItem = new QTableWidgetItem(prostota);

        ui->tableWidget->setItem(row, 0, elemItem); // Установка ячейки
        ui->tableWidget->setItem(row, 1, delItem); // Установка ячейки
        row++;

    }
}

