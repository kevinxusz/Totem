#ifndef PROPERTYOWNER_H
#define PROPERTYOWNER_H


#include "property.h"
#include "aggregation/aggregate.h"
#include "Utils/XML/xmlserializable.h"
#include <QString>
#include <QHash>
#include <QList>


namespace Utils
{
class XmlSerializer;
class XmlDeserializer;
}
namespace DesignNet
{
class Property;
class DESIGNNET_CORE_EXPORT PropertyOwner : public Utils::XmlSerializable
{
public:
	PropertyOwner();
	virtual ~PropertyOwner();

	Property*			getProperty(const QString& id) const;
	QList<Property*>	getProperties() const;
	virtual QString		name() const = 0;

	void				setPropertyGroupLabel(const QString& id, const QString& label);
	QString				propertyGroupLabel(const QString& id) const;

	virtual void		addProperty(Property* prop);
	virtual void		removeProperty(Property* prop);
	///
	/// signal-like 函数，由于不是QObject的类型，所以需要子类来完成消息通知
	/*!
	 * \brief 需要子类来实现该函数，该函数在属性移除前(还未调用setOwener(0))
	 * \param[in] prop 要移除的属性
	 */
	virtual void		propertyRemoving(Property* prop);
	/*!
	 * \brief propertyRemoved 属性已经移除，并且setOwner(0)
	 *
	 * \param[in] prop 移除的属性
	 */
	virtual void		propertyRemoved(Property* prop);
	virtual void		propertyAdded(Property* prop);

	/*!
	 * \fn	void PropertyOwner::serialize(Utils::XmlSerializer& s) const override;
	 *
	 * \brief	serialize this object to the given stream.
	 *
	 * \author	Michael
	 * \date	2015-11-05
	 *
	 * \param [in,out]	s	The Utils::XmlSerializer to process.
	 */
	
	void				serialize(Utils::XmlSerializer& s) const override;
	void				deserialize(Utils::XmlDeserializer& s) override {}


protected:

	Aggregation::Aggregate* m_aggregate; //!< 所有属性为一个整体，不可以删除
	QHash<QString, QString> m_propertyGroupIDLabelMap;//!< group id-->group在gui中的名称
	QString m_name;
};
}/// DesignNet namespace
#endif // PROPERTYOWNER_H
