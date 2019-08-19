

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','classnames','resolve!i18n','focus-drawer-HierarchyFilterMap','react','focus-drawer-TagsDrawer-TagInput','focus-drawer-TagsDrawer-TagSelectable','EvernoteDragUtil','lodash','css!focus/drawer/TagsDrawer/Tag'],function (require) {
  

  var classNames = require('classnames');
  var i18n = require('resolve!i18n');
  var HierarchyFilterMap = require('focus-drawer-HierarchyFilterMap');
  var React = require('react');
  var TagInput = require('focus-drawer-TagsDrawer-TagInput');
  var TagSelectable = require('focus-drawer-TagsDrawer-TagSelectable');
  var EvernoteDragUtil = require('EvernoteDragUtil');
  var _ = require('lodash');
  require('css!focus/drawer/TagsDrawer/Tag');

  function prefixedClass(suffix) {
    return 'focus-drawer-TagsDrawer-Tag-' + suffix;
  }

  /**
   * A tag that can recursively nest children tags. Each tag contains a TagInput,
   * which is hidden until the tag enters edit mode. The TagSelectable is the
   * normally-visbile portion that users can select, and also includes edit and delete
   * buttons. This tag also includes all children tags in its DOM structure.
   */
  var Tag = React.createClass({
    displayName: 'Tag',

    propTypes: {
      deleteIfConfirmed: React.PropTypes.func.isRequired,
      // Added by wrapping drag component
      depth: React.PropTypes.number.isRequired,
      // Added by wrapping drag component
      dragHandleClassName: React.PropTypes.string,
      // Added by wrapping drag component
      dragging: React.PropTypes.bool,
      // Added by wrapping drop area component
      dropActionString: React.PropTypes.string,
      dropHighlight: React.PropTypes.bool,
      editingTagKey: React.PropTypes.string,
      filterMap: React.PropTypes.instanceOf(HierarchyFilterMap),
      getTooltipContainer: React.PropTypes.func.isRequired,
      isBusinessTag: React.PropTypes.bool.isRequired,
      // Parent tag name only needed for de-nesting copy: "remove from <parentName>"
      parentName: React.PropTypes.string,
      rename: React.PropTypes.func.isRequired,
      select: React.PropTypes.func.isRequired,
      setChildrenHidden: React.PropTypes.func.isRequired,
      setEditingTagKey: React.PropTypes.func.isRequired,
      setParentKey: React.PropTypes.func.isRequired,
      setShortcut: React.PropTypes.func.isRequired,
      tag: React.PropTypes.shape({
        children: React.PropTypes.array.isRequired,
        childrenHidden: React.PropTypes.bool.isRequired,
        key: React.PropTypes.string.isRequired,
        modifiable: React.PropTypes.bool.isRequired,
        name: React.PropTypes.string.isRequired,
        parentKey: React.PropTypes.string,
        selected: React.PropTypes.bool.isRequired,
        shortcut: React.PropTypes.bool.isRequired
      }).isRequired
    },

    getInitialState: function getInitialState() {
      return {
        tagContainerWidth: null
      };
    },

    componentWillReceiveProps: function componentWillReceiveProps(nextProps) {
      if (this.props.editingTagKey === this.props.tag.key && this.props.tag.name !== nextProps.tag.name) {
        this.cancelEdit();
      }
    },

    shouldComponentUpdate: function shouldComponentUpdate(nextProps, nextState) {
      return !_.isEqual(this.props, nextProps) || !_.isEqual(this.state, nextState);
    },

    cancelEdit: function cancelEdit() {
      this.props.setEditingTagKey(null);
    },

    startEdit: function startEdit() {
      this.props.setEditingTagKey(this.props.tag.key);
    },

    render: function render() {
      var editing = this.props.editingTagKey === this.props.tag.key;
      var showChildren = (!this.props.tag.childrenHidden || this.props.filterMap) && !this.props.dragging;
      var switcherClassMap = {};
      var switcherClasses;

      switcherClassMap[prefixedClass('edit-mode')] = editing;
      switcherClassMap[prefixedClass('dragging')] = this.props.dragging;
      switcherClasses = classNames('qa-tagWidget', prefixedClass('input-switcher'), switcherClassMap);

      return React.createElement(
        'div',
        null,
        React.createElement(
          'div',
          { className: switcherClasses },
          React.createElement(TagInput, {
            tag: this.props.tag,
            cancelEdit: this.cancelEdit,
            editMode: editing,
            rename: this.props.rename
          }),
          React.createElement(TagSelectable, {
            tag: this.props.tag,
            depth: this.props.depth,
            editMode: editing,
            filterMap: this.props.filterMap,
            deleteIfConfirmed: this.props.deleteIfConfirmed,
            select: this.props.select,
            setChildrenHidden: this.props.setChildrenHidden,
            setShortcut: this.props.setShortcut,
            startEdit: this.startEdit,
            dragging: this.props.dragging,
            dragHandleClassName: this.props.dragHandleClassName,
            dropActionString: this.props.dropActionString,
            dropHighlight: this.props.dropHighlight,
            getTooltipContainer: this.props.getTooltipContainer
          })
        ),
        showChildren && this.props.tag.children.map(function (tag) {
          return (!this.props.filterMap || this.props.filterMap.getValue(tag.key)) && React.createElement(TagDraggableDroppable, {
            key: tag.key,
            tag: tag,
            parentName: this.props.tag.name,
            depth: this.props.depth + 1,
            editingTagKey: this.props.editingTagKey,
            filterMap: this.props.filterMap,
            isBusinessTag: this.props.isBusinessTag,
            deleteIfConfirmed: this.props.deleteIfConfirmed,
            rename: this.props.rename,
            setParentKey: this.props.setParentKey,
            select: this.props.select,
            setChildrenHidden: this.props.setChildrenHidden,
            setEditingTagKey: this.props.setEditingTagKey,
            setShortcut: this.props.setShortcut,
            getTooltipContainer: this.props.getTooltipContainer
          });
        }, this)
      );
    }
  });

  /**
   * Make the Tag component draggable
   */
  var TagDraggable = EvernoteDragUtil.createDragClass({
    reactClass: Tag,

    getDragItem: function getDragItem(props) {
      return {
        key: props.tag.key,
        name: props.tag.name,
        parentKey: props.tag.parentKey,
        parentName: props.parentName
      };
    },

    isDraggable: function isDraggable(props) {
      return !props.isBusinessTag && !props.filterMap && props.editingTagKey !== props.tag.key;
    },

    dropItemFilter: function dropItemFilter(dropItem) {
      return dropItem.type === 'tag-drop-area';
    },

    isMatchingKeys: function isMatchingKeys(a, b) {
      return a === b || !a && !b;
    },

    getHandleClassName: function getHandleClassName(props) {
      return prefixedClass('drag-handle-' + props.tag.key);
    },

    getDropDescriptor: function getDropDescriptor(dragItem, hoverDropItem) {
      if (hoverDropItem && !this.isMatchingKeys(dragItem.key, hoverDropItem.key) && !this.isMatchingKeys(dragItem.parentKey, hoverDropItem.key)) {
        return {
          dragItem: dragItem,
          dropItem: hoverDropItem
        };
      } else {
        return {
          dragItem: dragItem,
          dropItem: null
        };
      }
    },

    addProps: function addProps(dragItemState, dropDescriptor, props) {
      var dragging = dragItemState === EvernoteDragUtil.DRAG_STATE.DRAGGING;
      var dropActionString = null;
      if (dragging && dropDescriptor && dropDescriptor.dropItem) {
        dropActionString = dropDescriptor.dropItem.key === null ? i18n.L('Focus.drawer.moveTag.outside', [dropDescriptor.dragItem.parentName]) : i18n.L('Focus.drawer.moveTag.nestUnder', [dropDescriptor.dropItem.name]);
      }
      return {
        dragging: dragging,
        dropActionString: dropActionString,
        dragHandleClassName: this.getHandleClassName(props)
      };
    },

    onDrop: function onDrop(dropDescriptor, props) {
      if (dropDescriptor.dragItem && dropDescriptor.dropItem) {
        props.setParentKey(dropDescriptor.dragItem.key, dropDescriptor.dropItem.key);
        if (dropDescriptor.dropItem.key) {
          props.setChildrenHidden(dropDescriptor.dropItem.key, false);
        }
      }
    }
  });

  /**
   * Make the TagDraggable component a drop area
   */
  var TagDraggableDroppable = EvernoteDragUtil.createDropAreaClass({
    reactClass: TagDraggable,

    getDropItem: function getDropItem(props) {
      return {
        type: 'tag-drop-area',
        key: props.tag.key,
        name: props.tag.name
      };
    },

    addProps: function addProps(dropItem, dropDescriptor) {
      return {
        dropHighlight: dropDescriptor && _.isEqual(dropItem, dropDescriptor.dropItem)
      };
    }
  });

  return TagDraggableDroppable;
});