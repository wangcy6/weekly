

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react','css!focus/drawer/TagsDrawer/TagHeader'],function (require) {
  

  var React = require('react');
  require('css!focus/drawer/TagsDrawer/TagHeader');

  function prefixedClass(suffix) {
    return 'focus-drawer-TagsDrawer-TagHeader-' + suffix;
  }

  /**
   * A header with a single character, indicating that all tags below it start with this
   * character.
   */
  var TagHeader = React.createClass({
    displayName: 'TagHeader',

    propTypes: {
      label: React.PropTypes.string.isRequired
    },

    render: function render() {
      return React.createElement(
        'div',
        { className: prefixedClass('tag-header') },
        this.props.label
      );
    }
  });

  return TagHeader;
});