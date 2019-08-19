

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','focus-drawer-HierarchyFilterMap','react-infinite','react','react-dom','focus-drawer-TagsDrawer-Tag','focus-drawer-TagsDrawer-TagHeader','SimpleDropArea','css!focus/drawer/TagsDrawer/TagsList'],function (require) {
  

  var HierarchyFilterMap = require('focus-drawer-HierarchyFilterMap');
  var Infinite = require('react-infinite');
  var React = require('react');
  var ReactDOM = require('react-dom');
  var Tag = require('focus-drawer-TagsDrawer-Tag');
  var TagHeader = require('focus-drawer-TagsDrawer-TagHeader');
  var SimpleDropArea = require('SimpleDropArea');
  require('css!focus/drawer/TagsDrawer/TagsList');

  function prefixedClass(suffix) {
    return 'focus-drawer-TagsDrawer-TagsList-' + suffix;
  }

  var TAG_HEADER_HEIGHT = 44; // 35 margin-top, 11 height, -2 margin-bottom
  var TAG_HEIGHT = 36; // 12 margin-top, 24 height
  var TAG_MARGIN_BOTTOM = 12;

  /**
   * A list of tag headers and tags (which include any nested tags) in an infinitely
   * scrolling container.
   */
  var TagsList = React.createClass({
    displayName: 'TagsList',

    propTypes: {
      businessSelected: React.PropTypes.bool.isRequired,
      deleteIfConfirmed: React.PropTypes.func.isRequired,
      filterMap: React.PropTypes.instanceOf(HierarchyFilterMap),
      rename: React.PropTypes.func.isRequired,
      select: React.PropTypes.func.isRequired,
      setChildrenHidden: React.PropTypes.func.isRequired,
      setParentKey: React.PropTypes.func.isRequired,
      setShortcut: React.PropTypes.func.isRequired,
      tags: React.PropTypes.arrayOf(React.PropTypes.shape({
        children: React.PropTypes.array.isRequired,
        key: React.PropTypes.string.isRequired,
        name: React.PropTypes.string.isRequired
      })).isRequired
    },

    getInitialState: function getInitialState() {
      return {
        // should always be updated after mount
        containerHeight: 300,

        // guid of tag being edited if there is one, passed to all tags
        editingTagKey: null
      };
    },

    componentDidMount: function componentDidMount() {
      this.onResizeContainer();
      window.addEventListener('resize', this.onResizeContainer);
    },

    componentWillUnmount: function componentWillUnmount() {
      window.removeEventListener('resize', this.onResizeContainer);
    },

    onResizeContainer: function onResizeContainer() {
      var containerTop = this.getTagsContainer().getBoundingClientRect().top;
      this.setState({ containerHeight: window.innerHeight - containerTop });
    },

    /**
     * @param key is the guid of the tag to edit, or null to stop editing
     */
    setEditingTagKey: function setEditingTagKey(key) {
      this.setState({ editingTagKey: key });
    },

    getTagsContainer: function getTagsContainer() {
      return ReactDOM.findDOMNode(this);
    },

    getTagsWithHeaders: function getTagsWithHeaders() {
      var self = this;
      var heights = [];
      var tagElements = [];
      var lastFirstLetter;

      function getTotalTagsInTree(tag) {
        if (tag.childrenHidden) {
          return 1;
        } else {
          return tag.children.reduce(function (previousCount, childTag) {
            return previousCount + getTotalTagsInTree(childTag);
          }, 1);
        }
      }

      this.props.tags.forEach(function (tag) {
        var thisFirstLetter;
        if (!self.isFiltering()) {
          thisFirstLetter = tag.name[0].toUpperCase();
          if (thisFirstLetter !== lastFirstLetter) {
            lastFirstLetter = thisFirstLetter;
            tagElements.push(React.createElement(TagHeader, { key: thisFirstLetter, label: thisFirstLetter }));
            heights.push(TAG_HEADER_HEIGHT);
          }
        }

        if (!self.isFiltering() || self.props.filterMap.getValue(tag.key)) {
          tagElements.push(React.createElement(Tag, {
            key: tag.key,
            tag: tag,
            depth: 0,
            filterMap: self.props.filterMap,
            isBusinessTag: self.props.businessSelected,
            deleteIfConfirmed: self.props.deleteIfConfirmed,
            editingTagKey: self.state.editingTagKey,
            rename: self.props.rename,
            setParentKey: self.props.setParentKey,
            select: self.props.select,
            setChildrenHidden: self.props.setChildrenHidden,
            setEditingTagKey: self.setEditingTagKey,
            setShortcut: self.props.setShortcut,
            getTooltipContainer: self.getTagsContainer
          }));
          heights.push(getTotalTagsInTree(tag) * TAG_HEIGHT);
        }
      });

      // The last tag has additional bottom margin because its margin is not collapsed.
      if (heights.length) {
        heights[heights.length - 1] += TAG_MARGIN_BOTTOM;
      }

      return {
        tagElements: tagElements,
        heights: heights
      };
    },

    isFiltering: function isFiltering() {
      return !!this.props.filterMap;
    },

    render: function render() {
      var tagElementsMap = this.getTagsWithHeaders();
      return React.createElement(
        SimpleDropArea,
        { dropItem: { type: 'tag-drop-area', key: null } },
        React.createElement(
          Infinite,
          {
            className: prefixedClass('tags-container'),
            elementHeight: tagElementsMap.heights,
            containerHeight: this.state.containerHeight
          },
          tagElementsMap.tagElements
        )
      );
    }
  });

  return TagsList;
});