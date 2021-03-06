//
// Created by colors_wind on 2020/8/21.
//
#include <iostream>
#include <QMetaType>
#include "TokenStream.h"
#include "ExtendParser.h"
#include "ParseException.h"
#include "AlgorimatrixQt.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
int console();
int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp("nogui", argv[1]) == 0) {
        return console();
    }
    QApplication a(argc, argv);
    qRegisterMetaType<ParseResult>("ParseResult") ;
    AlgorimatrixQt w;
    w.show();
    return QApplication::exec();
}

int console() {
    char ch[100];
    ExtendParser parser;
    while(true) {
        cin.getline(ch, 256);
        parser.input(ch);
        if (string(ch) == "vars") {
            parser.printVariable();
            continue;
        }
        try {
            cout << parser.processS().getMessage() << endl;
        } catch (MatrixException &exception) {
            cerr << "ERROR: matrix error:\n\t" << exception.msg() << endl;
        } catch (ParseException &exception) {
            cerr << "ERROR: parse error:\n\t" << exception.msg() << endl;
        }
    }
}

