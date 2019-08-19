

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','classnames','resolve!i18n','focus-tooltip-Direction','focus-drawer-HierarchyFilterMap','react','focus-tooltip-WithTooltip','css!focus/drawer/TagsDrawer/TagSelectable'],function (require) {
  

  var classNames = require('classnames');
  var i18n = require('resolve!i18n');
  var Direction = require('focus-tooltip-Direction');
  var HierarchyFilterMap = require('focus-drawer-HierarchyFilterMap');
  var React = require('react');
  var WithTooltip = require('focus-tooltip-WithTooltip');
  require('css!focus/drawer/TagsDrawer/TagSelectable');

  function prefixedClass(suffix) {
    return 'focus-drawer-TagsDrawer-TagSelectable-' + suffix;
  }

  /**
   * The selectable portion of a tag, with edit and delete buttons. Shows the tag name and
   * note count.
   */
  var TagSelectable = React.createClass({
    displayName: 'TagSelectable',

    propTypes: {
      deleteIfConfirmed: React.PropTypes.func.isRequired,
      depth: React.PropTypes.number.isRequired,
      dragHandleClassName: React.PropTypes.string,
      dragging: React.PropTypes.bool,
      dropActionString: React.PropTypes.string,
      dropHighlight: React.PropTypes.bool,
      editMode: React.PropTypes.bool.isRequired,
      filterMap: React.PropTypes.instanceOf(HierarchyFilterMap),
      getTooltipContainer: React.PropTypes.func.isRequired,
      select: React.PropTypes.func.isRequired,
      setChildrenHidden: React.PropTypes.func.isRequired,
      setShortcut: React.PropTypes.func.isRequired,
      startEdit: React.PropTypes.func,
      tag: React.PropTypes.shape({
        children: React.PropTypes.array.isRequired,
        childrenHidden: React.PropTypes.bool.isRequired,
        count: React.PropTypes.number,
        key: React.PropTypes.string.isRequired,
        modifiable: React.PropTypes.bool.isRequired,
        name: React.PropTypes.string.isRequired,
        selected: React.PropTypes.bool.isRequired,
        shortcut: React.PropTypes.bool.isRequired
      }).isRequired
    },

    getInitialState: function getInitialState() {
      return {
        disableWidthTransition: true,
        iconsVisible: false,
        tagContainerWidth: null
      };
    },

    componentDidMount: function componentDidMount() {
      var self = this;
      this.setExplicitTagContainerWidth();

      // Workaround Safari treating "auto" as "0".
      this.disableWidthTransitionTimeoutId = setTimeout(function () {
        self.setState({ disableWidthTransition: false });
      }, 50);
    },

    componentDidUpdate: function componentDidUpdate(prevProps) {
      var self = this;
      if (prevProps.tag.name !== this.props.tag.name) {
        this.setExplicitTagContainerWidth();
      } else if (!!prevProps.filterMap !== !!this.props.filterMap || prevProps.tag.children.length !== this.props.tag.children.length) {
        // The disclosure's visibility may change; resize without any animation.
        this.setExplicitTagContainerWidth();
        this.setState({ disableWidthTransition: true });
        this.disableWidthTransitionTimeoutId = setTimeout(function () {
          self.setState({ disableWidthTransition: false });
        }, 50);
      }
    },

    componentWillUnmount: function componentWillUnmount() {
      clearTimeout(this.disableWidthTransitionTimeoutId);
      this.disableWidthTransitionTimeoutId = null;
    },

    disableWidthTransitionTimeoutId: null,

    handleClick: function handleClick(event) {
      if (event.target === this.refs.disclosure) {
        this.props.setChildrenHidden(this.props.tag.key, !this.props.tag.childrenHidden);
      } else {
        this.props.select(this.props.tag.key);
      }
    },

    onClickDelete: function onClickDelete() {
      this.props.deleteIfConfirmed(this.props.tag.key);
    },

    onClickShortcut: function onClickShortcut() {
      var addShortcut = !this.props.tag.shortcut;
      this.props.setShortcut(this.props.tag.key, addShortcut);
    },

    onMouseLeaveContainer: function onMouseLeaveContainer() {
      this.setState({ iconsVisible: false });
    },

    onMouseOverTag: function onMouseOverTag() {
      this.setState({ iconsVisible: true });
    },

    setExplicitTagContainerWidth: function setExplicitTagContainerWidth() {
      var nameWidth = this.refs.tagName.offsetWidth;
      var countWidth = this.refs.tagCount.offsetWidth;
      var disclosureWidth = this.refs.disclosure ? this.refs.disclosure.offsetWidth : 0;
      var extraPadding = 38;
      var totalWidth = nameWidth + countWidth + extraPadding + disclosureWidth;
      this.setState({ tagContainerWidth: totalWidth });
    },

    render: function render() {
      var actionContainerClassMap = {};
      var disclosureClassMap = {};
      var filterMap = this.props.filterMap;
      var filterMapValue = filterMap && filterMap.getValue(this.props.tag.key);
      var shortcutClassMap = {};
      var tagContainerClassMap = {};
      var topMatch = filterMap && filterMap.getTopMatch() === this.props.tag.key;
      var actionContainerClasses;
      var deleteClasses;
      var disclosureClasses;
      var editClasses;
      var shortcutClasses;
      var shortcutTooltipLabel;
      var showDisclosure = !!this.props.tag.children.length && !filterMap;
      var tagContainerClasses;
      var tagContainerStyle;
      var tagNameStyle;

      tagContainerClassMap[prefixedClass('edit-mode')] = this.props.editMode;
      tagContainerClassMap[prefixedClass('selected')] = !filterMap && this.props.tag.selected;
      tagContainerClassMap[prefixedClass('child')] = HierarchyFilterMap.CHILD === filterMapValue;
      tagContainerClassMap[prefixedClass('match')] = HierarchyFilterMap.MATCH === filterMapValue;
      tagContainerClassMap[prefixedClass('top-match')] = topMatch;
      tagContainerClassMap[prefixedClass('disable-transition')] = this.state.disableWidthTransition;
      tagContainerClassMap[prefixedClass('dragging')] = this.props.dragging;
      tagContainerClassMap[prefixedClass('drop-highlight')] = this.props.dropHighlight;
      tagContainerClasses = classNames(this.props.dragHandleClassName, 'qa-clickContainer', prefixedClass('container'), tagContainerClassMap);

      if (showDisclosure) {
        disclosureClassMap[prefixedClass('open')] = !this.props.tag.childrenHidden;
        disclosureClassMap[prefixedClass('closed')] = this.props.tag.childrenHidden;
        disclosureClasses = classNames(prefixedClass('disclosure'), disclosureClassMap);
      }

      tagContainerStyle = {
        width: this.state.tagContainerWidth
      };
      if (this.props.depth && !this.props.editMode) {
        tagContainerStyle.marginLeft = Math.min(228, this.props.depth * 12);
      }
      if (!this.props.dragging) {
        tagNameStyle = {
          maxWidth: 258 - (tagContainerStyle.marginLeft || 0)
        };
      }

      actionContainerClassMap[prefixedClass('hidden')] = !this.state.iconsVisible || this.props.editMode || this.props.dragging;
      actionContainerClasses = classNames(prefixedClass('action-container'), actionContainerClassMap);

      shortcutTooltipLabel = i18n.L('Focus.drawer.tooltip.' + (this.props.tag.shortcut ? 'removeShortcut' : 'addShortcut'));

      deleteClasses = prefixedClass('icon') + ' ' + prefixedClass('delete-icon') + ' qa-editButton';
      editClasses = prefixedClass('icon') + ' ' + prefixedClass('edit-icon') + ' qa-editButton';

      shortcutClassMap[prefixedClass('is-shortcut')] = this.props.tag.shortcut;
      shortcutClasses = classNames('qa-shortcutButton', prefixedClass('icon'), prefixedClass('shortcut-icon'), shortcutClassMap);

      return React.createElement(
        'div',
        { onMouseLeave: this.onMouseLeaveContainer },
        React.createElement(
          'div',
          {
            ref: 'tagContainer',
            onClick: this.handleClick,
            onMouseOver: this.onMouseOverTag,
            style: tagContainerStyle,
            className: tagContainerClasses
          },
          React.createElement(
            'div',
            { ref: 'tagName',
              className: prefixedClass('name') + ' qa-name',
              style: tagNameStyle
            },
            this.props.tag.name
          ),
          React.createElement(
            'div',
            { ref: 'tagCount', className: prefixedClass('count') + ' qa-count' },
            this.props.tag.count
          ),
          showDisclosure && React.createElement('div', { ref: 'disclosure', className: disclosureClasses }),
          React.createElement(
            'div',
            { key: 'dropActionString', className: prefixedClass('drop-action-string') },
            this.props.dropActionString
          )
        ),
        this.props.tag.modifiable && React.createElement(
          'div',
          { className: actionContainerClasses },
          React.createElement(
            WithTooltip,
            {
              className: prefixedClass('inline-block'),
              getTooltipContainer: this.props.getTooltipContainer,
              arrowDirection: Direction.UP,
              label: shortcutTooltipLabel
            },
            React.createElement('div', { onClick: this.onClickShortcut, className: shortcutClasses })
          ),
          React.createElement(
            WithTooltip,
            {
              className: prefixedClass('inline-block'),
              getTooltipContainer: this.props.getTooltipContainer,
              arrowDirection: Direction.UP,
              label: i18n.L('Focus.drawer.tooltip.editTag')
            },
            React.createElement('div', { onClick: this.props.startEdit, className: editClasses })
          ),
          React.createElement(
            WithTooltip,
            {
              className: prefixedClass('inline-block'),
              getTooltipContainer: this.props.getTooltipContainer,
              arrowDirection: Direction.UP,
              label: i18n.L('Focus.drawer.tooltip.deleteTag')
            },
            React.createElement('div', { onClick: this.onClickDelete, className: deleteClasses })
          )
        )
      );
    }
  });

  return TagSelectable;
});