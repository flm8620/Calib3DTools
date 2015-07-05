#ifndef CAMPOSWIDGET_H
#define CAMPOSWIDGET_H

#include <QWidget>
class QTableView;
class CamPosModel;
class CamPosWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CamPosWidget(QWidget *parent = 0);
    void setModel(CamPosModel *model);
    QTableView *getView();
public slots:
    void saveFile();
    void loadFile();
    void clear();
private:
    bool saveCamPos(const QStringList &list);
    bool loadCamPos(const QStringList &list);
    QTableView *tableView;
    CamPosModel *model;
};

#endif // CAMPOSWIDGET_H
