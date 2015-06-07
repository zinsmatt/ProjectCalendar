#ifndef PROGRAMMATIONTACHEDIALOG_H
#define PROGRAMMATIONTACHEDIALOG_H

#include <QDialog>
#include "tacheunitaire.h"
#include "agenda.h"
#include <QDateTime>


namespace Ui {
class ProgrammationTacheDialog;
}

class ProgrammationTacheDialog : public QDialog
{
    Q_OBJECT
    TacheUnitaire* tache;
public:
    explicit ProgrammationTacheDialog(TacheUnitaire* t,QWidget *parent = 0);
    ~ProgrammationTacheDialog();

private:
    Ui::ProgrammationTacheDialog *ui;

public slots:
    void activerDuree(int x);
    void accept();
};

#endif // PROGRAMMATIONTACHEDIALOG_H