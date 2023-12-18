#include "unit_of_work.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "domain_object.h"
#include <list>
#include <iostream>

UnitOfWork::UnitOfWork() {}

UnitOfWork* UnitOfWork::instance() {
    if(_instance == nullptr) {
        _instance = new UnitOfWork();
    }
    return _instance;
}


void UnitOfWork::registerNew(DomainObject * domainObject){
    _new[domainObject->id()] = domainObject;
};

void UnitOfWork::registerClean(DomainObject * domainObject){
    _clean[domainObject->id()] = domainObject;
};

void UnitOfWork::registerDirty(DomainObject * domainObject){
    if(inNew(domainObject->id())){
        _new.erase(domainObject->id());
    }
    _dirty[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
};

void UnitOfWork::registerDeleted(DomainObject * domainObject){
    if(inNew(domainObject->id())){
        _new.erase(domainObject->id());
    }
    _deleted[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
};

bool UnitOfWork::inNew(std::string id) const {
    return _new.count(id);
};

bool UnitOfWork::inClean(std::string id) const {
    return _clean.count(id);
};

bool UnitOfWork::inDirty(std::string id) const {
    return _dirty.count(id);
};

bool UnitOfWork::inDeleted(std::string id) const {
    return _deleted.count(id);
};

void UnitOfWork::commit(){
    for(const auto &dirty : _dirty){
        Drawing *drawing = dynamic_cast<Drawing *>(dirty.second);
        if(drawing != nullptr){
            DrawingMapper::instance()->update(dirty.first);
            registerClean(dirty.second);
        } else {
            PainterMapper::instance()->update(dirty.first);
            registerClean(dirty.second);
        }
    }
    _dirty.clear();

    for(const auto &item_new : _new){
        Drawing *drawing = dynamic_cast<Drawing *>(item_new.second);
        if(drawing != nullptr){
            DrawingMapper::instance()->add(item_new.second);
            registerClean(item_new.second);
        } else {
            PainterMapper::instance()->add(item_new.second);
            registerClean(item_new.second);
        }
    }
    _new.clear();

    for(const auto &item_deleted : _deleted){
        Drawing *drawing = dynamic_cast<Drawing *>(item_deleted.second);
        if(drawing != nullptr){
            DrawingMapper::instance()->del(item_deleted.first);
            registerClean(item_deleted.second);
        } else {
            PainterMapper::instance()->del(item_deleted.first);
            registerClean(item_deleted.second);
        }
    }
    _deleted.clear();
};

UnitOfWork * UnitOfWork::_instance = nullptr;

