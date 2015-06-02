#ifndef CLICKDIALOG_H
#define CLICKDIALOG_H

#include <QObject>
#include <QDialog>
class QPushButton;
class myScene;
class QStandardItemModel;
class QTableView;
class QFrame;
class MarkerImageView;
class ControllerTableView;
class QPushButton;
class QToolBar;
class ClickDialog : public QDialog
{
    Q_OBJECT
public:
    ClickDialog(const QImage& image, const QList<double> &coords, QWidget* parent=0);
    QList<double> getResult();
private:
    void initModel(const QList<double>& coords);
    QFrame* createControlPanel();
private slots:

    void getOnScreenToggled(bool toggle);
    void markerInsertedOnScreen();
private:
    QToolBar* toolBar;
    QStandardItemModel *model;
    ControllerTableView *tableView;
    MarkerImageView *markerImageView;
    QPushButton *placeButton;
};

#endif // CLICKDIALOG_H
