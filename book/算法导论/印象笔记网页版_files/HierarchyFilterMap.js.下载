/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define([],function() {
  

  /**
   * A map of keys to values that represent each object's relation to another object that
   * matches a filter value. The expected data should be provided as a list of trees,
   * where each tree describes a hierarchial relationship between the objects (e.g. nested
   * tags).
   *
   * If an object matches the filter value, then this map will set a value of
   * MATCH. If an object's ancestor was a match but it itself was not, then its value will
   * be CHILD. And otherwise if an object's descendant was a match, then it's value will
   * be PARENT. If the object, its ancestors, and its descendants do not match the filter
   * value, then it will be omitted from the map.
   */
  var HierarchyFilterMap = function() {
    this._map = {};
    this._topMatch = null;
  };

  HierarchyFilterMap.CHILD = 'CHILD';
  HierarchyFilterMap.MATCH = 'MATCH';
  HierarchyFilterMap.PARENT = 'PARENT';

  HierarchyFilterMap.prototype.getTopMatch = function() {
    return this._topMatch;
  };

  HierarchyFilterMap.prototype.getValue = function(key) {
    return this._map[key];
  };

  HierarchyFilterMap.prototype.markParent = function(key) {
    if (this._map[key] !== HierarchyFilterMap.MATCH
        && this._map[key] !== HierarchyFilterMap.CHILD) {
      this.setValue(key, HierarchyFilterMap.PARENT);
    }
    return this;
  };

  /**
   * Builds the map based on the provided filter value and data.
   *
   * @param {string} filterValue  a search string used to match data
   * @param {Array} dataArray  an array of data, where each element has a key field, a
   *     name field that is a string to be compared with filterValue, and a children field
   *     that is itself an array of data
   */
  HierarchyFilterMap.prototype.populate = function(filterValue, dataArray) {
    var self = this;
    var ancestorStack = [];
    var sanitizedFilterValue = filterValue.trim().toLowerCase();

    function isMatch(dataElement) {
      if (!sanitizedFilterValue) {
        return true;
      } else {
        return dataElement.name.toLowerCase().indexOf(sanitizedFilterValue) > -1;
      }
    }

    function findMatches(arr) {
      if (!arr || !arr.length) {
        return;
      }

      arr.forEach(function(dataElement) {
        var parentMatches;
        if (isMatch(dataElement)) {
          self.setValue(dataElement.key, HierarchyFilterMap.MATCH);
          ancestorStack.forEach(function(ancestorKey) {
            self.markParent(ancestorKey);
          });
        } else {
          parentMatches = ancestorStack.some(function(ancestorKey) {
            return self.getValue(ancestorKey) === HierarchyFilterMap.MATCH;
          });

          if (parentMatches) {
            self.setValue(dataElement.key, HierarchyFilterMap.CHILD);
          }
        }

        ancestorStack.push(dataElement.key);
        findMatches(dataElement.children);
        ancestorStack.pop();
      });
    }

    findMatches(dataArray);
    return this;
  };

  HierarchyFilterMap.prototype.setValue = function(key, value) {
    if (!this._topMatch) {
      this._topMatch = key;
    }
    this._map[key] = value;
    return this;
  };

  return HierarchyFilterMap;
});
