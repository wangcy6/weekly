

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','classnames','resolve!i18n','react','css!focus/drawer/BusinessToggle'],function (require) {
  

  var classNames = require('classnames');
  var i18n = require('resolve!i18n');
  var React = require('react');
  require('css!focus/drawer/BusinessToggle');

  function prefixedClass(suffix) {
    return 'focus-drawer-BusinessToggle-' + suffix;
  }

  /**
   * Side-by-side buttons of "Business" and "Personal".
   */
  var BusinessToggle = React.createClass({
    displayName: 'BusinessToggle',

    propTypes: {
      businessSelected: React.PropTypes.bool.isRequired,
      toggleBusiness: React.PropTypes.func
    },

    render: function render() {
      var businessClassMap = {
        'qa-business-toggle': true
      };
      var personalClassMap = {
        'qa-personal-toggle': true
      };
      var businessClasses;
      var personalClasses;

      businessClassMap[prefixedClass('selected')] = this.props.businessSelected;
      businessClasses = classNames(prefixedClass('toggle-button'), businessClassMap);

      personalClassMap[prefixedClass('selected')] = !this.props.businessSelected;
      personalClasses = classNames(prefixedClass('toggle-button'), personalClassMap);

      return React.createElement(
        'div',
        { className: prefixedClass('toggle-buttons') },
        React.createElement(
          'div',
          {
            className: businessClasses,
            onClick: this.props.toggleBusiness.bind(this, true)
          },
          i18n.L('Focus.drawer.toggle.business')
        ),
        React.createElement(
          'div',
          {
            className: personalClasses,
            onClick: this.props.toggleBusiness.bind(this, false)
          },
          i18n.L('Focus.drawer.toggle.personal')
        )
      );
    }
  });

  return BusinessToggle;
});