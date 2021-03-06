#ifndef AJOUTPROJETDIALOG_H
#define AJOUTPROJETDIALOG_H

#include <QDialog>

namespace Ui {
class AjoutProjetDialog;
}

/*! \class AjoutProjetDialog
        \brief Fenetre de dialogue pour la creation d'un projet
*/
class AjoutProjetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutProjetDialog(QWidget *parent = 0);
    ~AjoutProjetDialog();

private:
    Ui::AjoutProjetDialog *ui;

public slots:
    void accept();
};

#endif // AJOUTPROJETDIALOG_H
