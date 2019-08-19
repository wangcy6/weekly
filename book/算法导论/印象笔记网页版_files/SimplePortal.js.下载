

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 *
 * A simple react portal. Allows for rendering into a particular element on the page
 * or a new element appended to the body. The new element is automtically cleared when
 * the instance unmounts.
 */
define(['require','react','react-dom'],function (require) {
  

  var React = require('react');
  var ReactDOM = require('react-dom');

  var SimplePortal = React.createClass({
    displayName: 'SimplePortal',

    propTypes: {
      /**
       * The children to render at the other end of the portal. This is automatically
       * passed by React when there area any child elements in the jsx.
       */
      children: React.PropTypes.oneOfType([React.PropTypes.arrayOf(React.PropTypes.node), React.PropTypes.node]),

      /**
       * The html id of the element that the children should be rendered into. If
       * something falsy is passed, then the children will be rendered to a new div
       * appended to the body.
       */
      portalId: React.PropTypes.string
    },

    componentDidMount: function componentDidMount() {
      if (this.props.portalId) {
        this.portalElement = document.getElementById(this.props.portalId);
      } else {
        this.portalElement = document.createElement('div');
        document.body.appendChild(this.portalElement);
      }
      this.renderPortal();
    },

    componentDidUpdate: function componentDidUpdate() {
      this.renderPortal();
    },

    componentWillUnmount: function componentWillUnmount() {
      ReactDOM.unmountComponentAtNode(this.portalElement);
      if (!this.props.portalId) {
        document.body.removeChild(this.portalElement);
      }
    },

    portalElement: null,

    renderPortal: function renderPortal() {
      ReactDOM.render(React.createElement(
        'div',
        null,
        this.props.children
      ), this.portalElement);
    },

    render: function render() {
      return null;
    }
  });

  return SimplePortal;
});