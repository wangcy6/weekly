

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','resolve!i18n','focus-drawer-BusinessToggle','focus-tooltip-Direction','focus-drawer-Filter','focus-drawer-HelpIllustration','focus-drawer-HierarchyFilterMap','focus-drawer-LoadingSpinner','react','focus-drawer-TagsDrawer-TagsList','focus-tooltip-WithTooltip','css!focus/drawer/TagsDrawer/TagsDrawer'],function (require) {
  

  var i18n = require('resolve!i18n');
  var BusinessToggle = require('focus-drawer-BusinessToggle');
  var Direction = require('focus-tooltip-Direction');
  var Filter = require('focus-drawer-Filter');
  var HelpIllustration = require('focus-drawer-HelpIllustration');
  var HierarchyFilterMap = require('focus-drawer-HierarchyFilterMap');
  var LoadingSpinner = require('focus-drawer-LoadingSpinner');
  var React = require('react');
  var TagsList = require('focus-drawer-TagsDrawer-TagsList');
  var WithTooltip = require('focus-tooltip-WithTooltip');
  require('css!focus/drawer/TagsDrawer/TagsDrawer');

  function prefixedClass(suffix) {
    return 'focus-drawer-TagsDrawer-TagsDrawer-' + suffix;
  }

  /**
   * A view for tags with a label, a business toggle (for business users), a search box
   * for filtering tags, and a tags list.
   */
  var TagsDrawer = React.createClass({
    displayName: 'TagsDrawer',

    propTypes: {
      businessSelected: React.PropTypes.bool.isRequired,
      businessUser: React.PropTypes.bool.isRequired,
      isBobUser: React.PropTypes.bool.isRequired,
      presenter: React.PropTypes.shape({
        deleteIfConfirmed: React.PropTypes.func.isRequired,
        rename: React.PropTypes.func.isRequired,
        select: React.PropTypes.func.isRequired,
        setChildrenHidden: React.PropTypes.func.isRequired,
        setParentKey: React.PropTypes.func.isRequired,
        setShortcut: React.PropTypes.func.isRequired,
        showCreateTagDialog: React.PropTypes.func.isRequired,
        toggleBusiness: React.PropTypes.func
      }).isRequired,
      tags: React.PropTypes.arrayOf(React.PropTypes.shape({
        key: React.PropTypes.string.isRequired,
        name: React.PropTypes.string.isRequired,
        parentKey: React.PropTypes.string
      }))
    },

    getInitialState: function getInitialState() {
      return {
        filterMap: null,
        filterValue: ''
      };
    },

    componentWillMount: function componentWillMount() {
      this.setState({
        nestedTags: this.getNestedTags(this.props.tags)
      });
    },

    componentWillReceiveProps: function componentWillReceiveProps(nextProps) {
      if (this.props.tags !== nextProps.tags) {
        this.setState({
          filterMap: this.getFilterMap(this.state.filterValue),
          nestedTags: this.getNestedTags(nextProps.tags)
        });
      }
      if (this.props.businessSelected !== nextProps.businessSelected) {
        this.setFilterValue('');
      }
    },

    onEnterFilter: function onEnterFilter() {
      var topMatch = this.state.filterMap && this.state.filterMap.getTopMatch();
      if (topMatch) {
        this.props.presenter.select(topMatch);
      }
    },

    getFilterMap: function getFilterMap(filterValue) {
      return filterValue ? new HierarchyFilterMap().populate(filterValue, this.props.tags) : null;
    },

    getNestedTags: function getNestedTags(tags) {
      var tagsMap;
      if (!tags) {
        return null;
      }

      tags.sort(this.tagNameComparator);

      tagsMap = {};
      tags.forEach(function (tag) {
        tagsMap[tag.key] = tag;
        tag.children = [];
      });

      tags.forEach(function (tag) {
        if (tag.parentKey && tagsMap[tag.parentKey]) {
          tagsMap[tag.parentKey].children.push(tag);
        }
      });

      return tags.filter(function (tag) {
        return !tag.parentKey || !tagsMap[tag.parentKey];
      });
    },

    setFilterValue: function setFilterValue(filterValue) {
      this.setState({
        filterMap: this.getFilterMap(filterValue),
        filterValue: filterValue
      });
    },

    tagNameComparator: function tagNameComparator(tagA, tagB) {
      return tagA.name.toUpperCase() < tagB.name.toUpperCase() ? -1 : 1;
    },

    render: function render() {
      var loading = !this.state.nestedTags;
      var lessThanTwoTags = !this.state.nestedTags || !this.state.nestedTags.length || this.state.nestedTags.length === 1 && !this.state.nestedTags[0].children.length;
      var showHelpIllustration = !loading && lessThanTwoTags && !this.state.filterValue;
      var showToggle = this.props.businessUser && !this.props.isBobUser;

      return React.createElement(
        'div',
        { className: 'qa-tags-drawer' },
        React.createElement(
          'div',
          { className: prefixedClass('header') },
          i18n.L('Focus.drawer.header.tags'),
          this.props.businessSelected ? null : React.createElement(
            WithTooltip,
            {
              className: prefixedClass('no-text-transform'),
              arrowDirection: Direction.UP,
              label: i18n.L('Focus.drawer.tooltip.createTag')
            },
            React.createElement('div', {
              className: prefixedClass('create-tag-icon'),
              onClick: this.props.presenter.showCreateTagDialog
            })
          )
        ),
        showToggle && React.createElement(BusinessToggle, {
          businessSelected: this.props.businessSelected,
          toggleBusiness: this.props.presenter.toggleBusiness
        }),
        React.createElement(
          'div',
          { className: prefixedClass('filter-container') },
          React.createElement(Filter, {
            filterValue: this.state.filterValue,
            handleEnter: this.onEnterFilter,
            setFilterValue: this.setFilterValue
          })
        ),
        React.createElement(
          'div',
          { className: prefixedClass('body-container') },
          loading ? React.createElement(LoadingSpinner, null) : React.createElement(TagsList, {
            tags: this.state.nestedTags,
            filterMap: this.state.filterMap,
            businessSelected: this.props.businessSelected,
            deleteIfConfirmed: this.props.presenter.deleteIfConfirmed,
            rename: this.props.presenter.rename,
            setParentKey: this.props.presenter.setParentKey,
            select: this.props.presenter.select,
            setChildrenHidden: this.props.presenter.setChildrenHidden,
            setShortcut: this.props.presenter.setShortcut
          }),
          showHelpIllustration && React.createElement(
            HelpIllustration,
            {
              body: i18n.L('Focus.drawer.empty.body'),
              imageClass: prefixedClass('help-image')
            },
            React.createElement('span', { dangerouslySetInnerHTML: { __html: i18n.L('Focus.drawer.empty.header', [prefixedClass('bold')]) }
            })
          )
        )
      );
    }
  });

  return TagsDrawer;
});