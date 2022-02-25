#pragma once

#include "workpackage.h"

WorkPackage::WorkPackage(const QJsonObject& json) {
    if (json.contains("_type") && json["_type"] == "WorkPackage") {
        id = getInt(json["id"]);
        subject = getString(json["subject"]);
        description = getString(json["description"]["raw"]);
        startDate = getString(json["startDate"]);
        dueDate = getString(json["dueDate"]);
        estimatedTime = getString(json["estimatedTime"]);
        createdAt = getString(json["createdAt"]);
        updatedAt = getString(json["updatedAt"]);
        type = getString(json["_links"]["type"]["title"]);
        priority = getString(json["_links"]["priority"]["title"]);
        project = getString(json["_links"]["project"]["title"]);
        status = getString(json["_links"]["status"]["title"]);
        parentName = getString(json["_links"]["parent"]["title"]);
        parentID = getHrefID(json["_links"]["parent"]["href"]);

		try {
            loginName = getString(json["customField11"]);
            lanIP = getString(json["customField12"]);
            wanIP = getString(json["customField13"]);
            teamViewerID = getInt(json["customField14"]);
            machineNumber = getInt(json["customField15"]);
		}
		catch (std::exception& e) {
			
		}

	}
}

int WorkPackage::getHrefID(const QJsonValue& el) const {
    QString href = getString(el);
    if (href.isEmpty())
        return 0;
    return href.chopped(href.lastIndexOf('/')).toInt();
}

QString WorkPackage::getString(const QJsonValue& el) const {
    if (el.isString())
        return el.toString();
    return QString();
}

int WorkPackage::getInt(const QJsonValue& el) const {
    if(el.isDouble())
        return el.toInt();
    return 0;
}

void WorkPackage::print() const {
    std::cout << type.constData() << "\n"
		<< " id           :  " << id << "\n"
        << " subject      :  " << subject.constData() << "\n"
        << " description  :  " << description.constData() << "\n"
        << " startDate    :  " << startDate.constData() << "\n"
        << " dueDate      :  " << dueDate.constData() << "\n"
        << " estimatedTime:  " << estimatedTime.constData() << "\n"
        << " cretedAt     :  " << createdAt.constData() << "\n"
        << " updatedAt    :  " << updatedAt.constData() << "\n"
        << " priority     :  " << priority.constData() << "\n"
        << " project      :  " << project.constData() << "\n"
        << " startDate    :  " << startDate.constData() << "\n"
        << " parentID     :  " << parentID << "\n"
        << " parentName   :  " << parentName.constData() << "\n";
}

bool WorkPackage::isType(const QJsonObject& json, const QString& type) const{
    QString workPackageType = getString(json["_links"]["type"]["title"]);
    return workPackageType == type;
}