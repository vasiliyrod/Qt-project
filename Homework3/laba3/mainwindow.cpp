#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    ui->treeView->setModel(model);

    loadXML("organization.xml", 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadXML(const QString &fileName, bool is_del = 0) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot open XML file");
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        QMessageBox::critical(this, "Error", "Cannot parse XML file");
        file.close();
        return;
    }
    file.close();

    model->clear();
    QDomElement root = doc.documentElement();
    QString root_name = root.tagName();
    if (root_name == "Organization") root_name = "Организация";
    model->setHorizontalHeaderLabels(QStringList() << root_name);

    // Получаем корневой элемент модели
    QStandardItem *rootItem = model->invisibleRootItem();

    parseElement(root, rootItem, is_del);
}

void MainWindow::parseElement(const QDomElement &element, QStandardItem *parentItem, bool is_del) {
    QDomNode node = element.firstChild();
    while (!node.isNull()) {
        if (node.isElement()) {
            QDomElement childElement = node.toElement();

            // Проверяем, является ли элемент <Employee>
            if (childElement.tagName() == "Employee") {
                QString employeeText;
                QDomNode childNode = childElement.firstChild();

                while (!childNode.isNull()) {
                    if (childNode.isElement()) {
                        QDomElement subElement = childNode.toElement();
                        if (subElement.tagName() == "name") {
                            employeeText += subElement.text();
                        } else if (subElement.tagName() == "experience") {
                            employeeText += " (стаж: " + subElement.text() + ")";
                        }
                    }
                    childNode = childNode.nextSibling();
                }
                if (!(employeeText == "Алексей Смирнов (стаж: 3 года)" && is_del)) {
                    QStandardItem *item = new QStandardItem(employeeText);
                    parentItem->appendRow(item);
                }
            } else {
                // Если не <Employee>, то просто создаем узел
                QString nodeText;
                if (childElement.hasAttribute("name")) {
                    nodeText += childElement.attribute("name");
                } else if (childElement.hasAttribute("title")) {
                    nodeText += childElement.attribute("title");
                }

                QStandardItem *item = new QStandardItem(nodeText);
                parentItem->appendRow(item);
                parseElement(childElement, item, is_del);
            }
        }
        node = node.nextSibling();
    }
}


void MainWindow::on_pushButton_clicked()
{
    loadXML("organization.xml", 1);
}

