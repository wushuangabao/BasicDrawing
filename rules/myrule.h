#ifndef MYRULE_H
#define MYRULE_H

#include <QtMath>
#include <QPointF>
#include <QPainterPath>
#include <QList>
#include <QMap>
#include <QStringList>

struct Line{
    QPointF p1;
    QPointF p2;
};

/**
 * @brief 制板规则类
 */
class MyRule
{
private:
    QStringList types;  /**< 实体类型表 */
    QStringList pFuncs; /**< 点的方法名称表 */
    QString file;       /**< 规则文件路径 */
    QString entityOut;  /**< 输出实体名 */

    void info(QString info);
    bool setInput(QString type, QString name);

public:
    MyRule(QString file);
    ~MyRule();

    // 基本约束方法
    QPointF pFunc(QString func, int idFunc = -1); // 求点的方法集合
    QPointF offset(QPointF p1, qreal distance, QPointF direction);
    QPointF extend(Line l1, qreal length, Line lFixLength);
    QPointF foot(QPointF p1, Line l1);
    QPointF divide(QPointF p1, QPointF p2, qreal proprtion);
    QPointF cross(Line l1, Line l2);
    Line line(QPointF p1, QPointF p2);
    // 圆滑 直接用drawPath(QList<QPointF> curve)实现

    // 所有实体的表：
    QMap<QString,QString> params;        /**< 参数型实体 */
    QMap<QString,QPointF> points;        /**< 点类型实体 */
    QMap<QString,Line> lines;            /**< 直线型实体 */
    QMap<QString,QList<QPointF>> curves; /**< 曲线型实体 */

    // 规则代码解析：
    bool parseCode(QString code);
    QStringList getEntityNames(QString code);
    QString getEntityType(QString code);
    QString getTypeOf(QString name);
    QString getValue(QString code);
    void defineEntity(QString code);
    void defineEntity(QString type, QString name);
    void assignEntity(QString code);
    void assignEntity(QString name, QString value);
    qreal param(QString value, bool* ok = nullptr);
    QPointF point(QString value, bool* ok = nullptr);
    Line line(QString value, bool* ok = nullptr);
    QList<QPointF> curve(QString value, bool* ok = nullptr);

    // 使用自定义规则：
    QString callRule(QString file);
    QString callRule(QString file,QString input);
    QString callRule(QString file,QStringList input);

    // 生成绘图路径：
    QPainterPath drawPath();
    QPainterPath drawPath(QString name);
    QPainterPath drawPath(QPointF p);
    QPainterPath drawPath(Line l);
    QPainterPath drawPath(QList<QPointF> curve);  // todo: 实现贝塞尔插值曲线

    // 辅助工具函数：
    static bool left(QPointF p1, QPointF p2);
    static bool up(QPointF p1, QPointF p2);
    static qreal calculate(QString expression, bool* ok = nullptr);
    static QPointF endPoint(Line l, QString s, bool* ok = nullptr);
    static QPointF endPoint(QPointF p1, QPointF p2, QString s, bool* ok = nullptr);
};

#endif // MYRULE_H
